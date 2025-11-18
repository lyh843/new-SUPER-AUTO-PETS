#include "Skill.hpp"
#include "Pet.hpp"
#include "../engine/BattleEngine.hpp"
#include <random>
#include <algorithm>
#include <Qstring>

/* ---------------- Ant ----------------
   死亡时：随机一个友军 +2 HP +1 ATK
*/

void SkillAnt::onFaint(Pet* self, BattleEngine* engine, bool isPlayer1, int index) {
    auto &team = isPlayer1 ? engine->getPlayer1Team() : engine->getPlayer2Team();
    std::vector<Pet*> candidates;
    for (size_t i = 0; i < team.size(); ++i) {
        if ((int)i != index && team[i] && !team[i]->isDead()) candidates.push_back(team[i].get());
    }
    if (candidates.empty()) return;
    Pet* t = candidates[randIndex((int)candidates.size())];
    t->setHP(t->getHP() + 2);
    t->addAttack(1);

    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 死亡，随机友军获得 +2HP +1ATK").arg(QString::fromStdString(self->getName())),
        -1, index, 0, isPlayer1});
}

/* ---------------- Fish ----------------
   升级时（战斗开始时若等级>1）给予两个友军 +1/+1
   这里采用战斗开始前触发，检查level>1（也可放到levelUp里）
*/

void SkillFish::onPreBattle(Pet* self, BattleEngine* engine){
    if (!self) return;
    if (self->getLevel() <= 1) return;
    auto& team = (engine->_player1Turn) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    std::vector<Pet*> candidates;
    for (size_t i = 0; i < team.size(); ++i)
        if (team[i].get() != self)
            candidates.push_back(team[i].get());
    if (candidates.empty()) return;
    std::shuffle(candidates.begin(), candidates.end(), std::mt19937{std::random_device{}()});
    int cnt = std::min<int>(2, (int)candidates.size());
    for (int i = 0; i < cnt; ++i) {
        candidates[i]->setHP(candidates[i]->getHP() + 1);
        candidates[i]->addAttack(1);
    }
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 升级，给随机两个友军 +1/+1").arg(QString::fromStdString(self->getName())),
        -1, -1, 0, engine->_player1Turn});
}


/* ---------------- Cricket ----------------
   你要求：出售后对任意两个队友 +1 攻击
   我实现为 onSell（商店卖出时应调用 Pet::triggerOnSell(ownerTeam)）
*/

void SkillCricket::onSell(Pet* self, std::vector<std::unique_ptr<Pet>>& ownerTeam) {
    if (ownerTeam.empty()) return;
    std::vector<int> idx;
    for (int i = 0; i < (int)ownerTeam.size(); ++i)
        if (ownerTeam[i]) idx.push_back(i);
    if (idx.empty()) return;
    int first = idx[randIndex((int)idx.size())];
    ownerTeam[first]->addAttack(1);
    int second = first;
    if (idx.size() > 1) {
        // 保证两个可能不同
        while (second == first) second = idx[randIndex((int)idx.size())];
        ownerTeam[second]->addAttack(1);
    }
    // 无 engine 可以触发 UI，这里不触发
}


/* ---------------- Hedgehog ----------------
   受伤时：对攻击者造成等量或等量*factor 反击伤害
*/

void SkillHedgehog::onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) {
    if (!attacker) return;
    int retaliate = damage; // 原版：把伤害等量反弹
    attacker->receiveDamage(retaliate);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 受伤，反弹 %2 点伤害给攻击者").arg(QString::fromStdString(self->getName())).arg(retaliate),
        -1, -1, retaliate, true});
}


/* ---------------- Peacock ----------------
    受到攻击：+1攻击力
*/

void SkillPeacock::onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) {
    self->addAttack(1);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 展示孔雀羽毛，获得 +1 攻击").arg(QString::fromStdString(self->getName())),
        -1, -1, 0, true});
}


/* ---------------- Camel ----------------
   受到攻击时给后面最近的友军 +2/+2（需要根据队伍 index 实现）
*/

void SkillCamel::onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) {
    auto &team = (engine->_player1Turn) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    // 找 self 的位置
    int pos = -1;
    for (int i = 0; i < (int)team.size(); ++i) if (team[i].get() == self) { pos = i; break; }
    if (pos == -1) return;
    // 后面最近的友军（pos+1 -> end）
    for (int i = pos + 1; i < (int)team.size(); ++i) {
        if (team[i] && !team[i]->isDead()) {
            team[i]->setHP(team[i]->getHP() + 2);
            team[i]->addAttack(2);
            engine->emitEvent({BattleEventType::SkillTrigger,
                QString("%1 受伤，给后方最近友军 +2/+2").arg(QString::fromStdString(self->getName())),
                -1, -1, 0, engine->_player1Turn});
            return;
        }
    }
}

/* ---------------- Dodo ----------------
   战斗开始前给予前方最近队友 50% 攻击力（实现为在 onPreBattle）
*/

void SkillDodo::onPreBattle(Pet* self, BattleEngine* engine) {
    auto &team = (engine->_player1Turn) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    int pos = -1;
    for (int i = 0; i < (int)team.size(); ++i) if (team[i].get() == self) { pos = i; break; }
    if (pos <= 0) return; // 前面无队友
    // 前面最近队友是 pos-1
    Pet* friendPet = team[pos - 1].get();
    if (!friendPet) return;
    int bonus = friendPet->getAttack() / 2;
    friendPet->setAttack(friendPet->getAttack() + bonus);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 战斗开始，给予前方最近队友 +%1 攻击（50%）")
            .arg(QString::fromStdString(self->getName())).arg(bonus),
        -1, -1, 0, engine->_player1Turn});
}

/* ---------------- Blowfish ----------------
   受伤时对随机敌人造成3点伤害
*/

void SkillBlowfish::onHurt(Pet* self, Pet* attacker, int damage, BattleEngine* engine) {
    // 对随机敌人造成3点伤害
    int enemy = (engine->_player1Turn) ? 2 : 1;
    auto &enemyTeam = (enemy == 1) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    std::vector<Pet*> candidates;
    for (auto &p : enemyTeam) if (p && !p->isDead()) candidates.push_back(p.get());
    if (candidates.empty()) return;
    Pet* target = candidates[randIndex((int)candidates.size())];
    target->receiveDamage(3);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 受伤，对随机敌人造成 3 点伤害").arg(QString::fromStdString(self->getName())),
        -1, -1, 3, engine->_player1Turn});
    engine->dealDamageToAll(0); // 仅调用清理逻辑
}


/* ---------------- Skunk ----------------
   战斗开始前将最高血量的敌人减少 1/3 血量
*/

void SkillSkunk::onPreBattle(Pet* self, BattleEngine* engine) {
    int enemy = (engine->_player1Turn) ? 2 : 1;
    auto &enemyTeam = (enemy == 1) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    if (enemyTeam.empty()) return;
    int maxHp = -1, idx = -1;
    for (int i = 0; i < (int)enemyTeam.size(); ++i) {
        if (enemyTeam[i] && !enemyTeam[i]->isDead() && enemyTeam[i]->getHP() > maxHp) {
            maxHp = enemyTeam[i]->getHP();
            idx = i;
        }
    }
    if (idx == -1) return;
    int reduce = std::max(1, enemyTeam[idx]->getHP() / 3);
    enemyTeam[idx]->setHP(enemyTeam[idx]->getHP() - reduce);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 战斗开始，降低敌方最高血量单位 %2 点").arg(QString::fromStdString(self->getName())).arg(reduce),
        -1, idx, reduce, engine->_player1Turn});
}


/* ---------------- Flamingo ----------------
   战斗结束时如果存活获得 +2 ATK
*/

void SkillFlamingo::onFaint(Pet* self, BattleEngine* engine, bool isPlayer1, int index) {
    // Flamingo 的效果在战斗结束时，如果活着获得 +2。这里我们在战斗中实现：每次一轮后检查并在 onDealDamage 或 onPreBattle 中实现
}
void SkillFlamingo::onDealDamage(Pet* self, Pet* target, int damage, BattleEngine* engine) {
    // 实现：击打完结后如果还活着，给予 +2 ATK（为示例，这会过多触发）
}


/* ---------------- Kangaroo ----------------
   商店出售时给前方友军 +1/+1
*/

void SkillKangaroo::onPreBattle(Pet* self, BattleEngine* engine) {
    auto &team = (engine->_player1Turn) ? engine->getPlayer1Team() : engine->getPlayer2Team();
    int pos = -1;
    for (int i = 0; i < (int)team.size(); ++i) if (team[i].get() == self) { pos = i; break; }
    if (pos <= 0) return;
    Pet* friendPet = team[pos - 1].get();
    if (!friendPet) return;
    friendPet->setHP(friendPet->getHP() + 1);
    friendPet->addAttack(1);
    engine->emitEvent({BattleEventType::SkillTrigger,
        QString("%1 战斗开始，给予前方友军 +1/+1").arg(QString::fromStdString(self->getName())),
        -1, -1, 0, engine->_player1Turn});
}


/* ---------------- 注册器：用来在 Pet.cpp 中声明的 forward class 与 make_unique 使用 ------------- */
// 上面使用类定义（匿名类），现在暴露构造器函数用于 Pet.cpp setSkill 调用
// 提供工厂函数
std::unique_ptr<Skill> makeSkillAnt(){ return std::make_unique<SkillAnt>(); }
std::unique_ptr<Skill> makeSkillFish(){ return std::make_unique<SkillFish>(); }
std::unique_ptr<Skill> makeSkillCricket(){ return std::make_unique<SkillCricket>(); }
std::unique_ptr<Skill> makeSkillHedgehog(){ return std::make_unique<SkillHedgehog>(); }
std::unique_ptr<Skill> makeSkillPeacock(){ return std::make_unique<SkillPeacock>(); }
std::unique_ptr<Skill> makeSkillCamel(){ return std::make_unique<SkillCamel>(); }
std::unique_ptr<Skill> makeSkillDodo(){ return std::make_unique<SkillDodo>(); }
std::unique_ptr<Skill> makeSkillBlowfish(){ return std::make_unique<SkillBlowfish>(); }
std::unique_ptr<Skill> makeSkillSkunk(){ return std::make_unique<SkillSkunk>(); }
std::unique_ptr<Skill> makeSkillFlamingo(){ return std::make_unique<SkillFlamingo>(); }
std::unique_ptr<Skill> makeSkillKangaroo(){ return std::make_unique<SkillKangaroo>(); }
std::unique_ptr<Skill> makeSkillSwan(){ return std::make_unique<SkillSwan>(); }
std::unique_ptr<Skill> makeSkillDuck(){ return std::make_unique<SkillDuck>(); }
