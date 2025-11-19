#include "Pet.hpp"
#include <algorithm>
#include "Food.hpp"

class SkillAnt;
class SkillFish;
class SkillCricket;
class SkillHedgehog;
class SkillPeacock;
class SkillCamel;
class SkillDodo;
class SkillBlowfish;
class SkillSkunk;
class SkillFlamingo;
class SkillKangaroo;
class SkillSwan;
class SkillDuck;

//宠物基类拷贝构造函数
Pet::Pet(const Pet& other)
    : _name(other._name)
    , _chineseName(other._chineseName)
    , _hp(other._hp)
    , _damage(other._damage)
    , _ownerPlayer(other._ownerPlayer)
    , _level(other._level)
    , _exp(other._exp)
    , _tier(other._tier)
    , _baseHP(other._baseHP)
    , _baseAttack(other._baseAttack)
    , _foodPerk(other._foodPerk)
    , _hasArmor(other._hasArmor)
    , _canRevive(other._canRevive)
    , _hasMelonShield(other._hasMelonShield)
{}

// 实现升级逻辑
void Pet::levelUp()
{
    if (_level >= 3)
        return;  // 已达最高等级

    _level++;

    // 升级时提升属性：每级增长50%的基础属性
    int hpBonus     = _baseHP / 2 + 1;
    int attackBonus = _baseAttack / 2 + 1;

    _hp += hpBonus;
    _damage += attackBonus;
}

// 实现获得经验的逻辑
void Pet::gainExperience(int amount)
{
    _exp += amount;

    // 每2点经验升一级，最高3级
    // exp 0-1: level 1
    // exp 2-3: level 2
    // exp 4+:  level 3
    int targetLevel = std::min(3, 1 + _exp / 2);

    // 如果目标等级大于当前等级，则升级
    while (_level < targetLevel)
    {
        levelUp();
    }
}

// 实现应用食物的方法
bool Pet::applyFood(std::unique_ptr<Food>& food)
{
    if (!food)
        return false;

    // 应用食物效果（新的食物会覆盖旧的Food Perk）
    bool applied = food->applyToPet(this);

    if (applied)
    {
        // 更新Food Perk类型
        _foodPerk = food->getPerkType();

        // 根据食物类型设置特殊标记
        switch (food->getPerkType())
        {
        case FoodPerkType::Garlic:
            _hasArmor = true;
            break;
        case FoodPerkType::Mushroom:
            _canRevive = true;
            break;
        case FoodPerkType::Melon:
            _hasMelonShield = true;
            break;
        default:
            break;
        }
    }

    return applied;
}

void Pet::triggerPreBattleSkill(BattleEngine* engine) {
    if (_skill) _skill->onPreBattle(this, engine);
}

void Pet::triggerOnAttack(Pet* target, BattleEngine* engine) {
    if (_skill) _skill->onAttack(this, target, engine);
}

void Pet::triggerOnHurt(Pet* attacker, int damage, BattleEngine* engine) {
    if (_skill) _skill->onHurt(this, attacker, damage, engine);
}

void Pet::triggerOnDealDamage(Pet* target, int damage, BattleEngine* engine) {
    if (_skill) _skill->onDealDamage(this, target, damage, engine);
}

void Pet::triggerOnFaint(BattleEngine* engine, bool isPlayer1, int index) {
    if (_skill) _skill->onFaint(this, engine, isPlayer1, index);
}

void Pet::triggerOnFriendFaint(Pet* faintedFriend, BattleEngine* engine, bool isPlayer1, int indexOfFainted) {
    if (_skill) _skill->onFriendFaint(this, faintedFriend, engine, isPlayer1, indexOfFainted);
}

void Pet::triggerOnSell(std::vector<std::unique_ptr<Pet>>& ownerTeam) {
    if (_skill) _skill->onSell(this, ownerTeam);
}

void Pet::onStartBattle() {
    if (_skill)
        _skill->onStart(this);
}

// 派生类构造函数实现

Cat::Cat(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Pig", "猪", "朴实无华的一只小猪", hp, attack, ownerPlayer, tier){}

Ant::Ant(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Ant", "蚂蚁", "死亡时给随机友方宠物+2HP/+1ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillAnt>());
}

Fish::Fish(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Fish", "鱼", "升级时给随机两个友方宠物+1HP/+1ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillFish>());
}

Cricket::Cricket(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Turtle", "乌龟", "出售以后对任意的两个队友+1ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillCricket>());
}

Duck::Duck(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Duck", "鸭", "出售给所有玩家宠物+1HP", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillDuck>());
}

Swan::Swan(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Swan", "天鹅", "回合开始时获得1金币", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillSwan>());
}

Flamingo::Flamingo(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Flamingo", "火烈鸟", "战斗结束时如果存活获得+2ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillFlamingo>());
}

Hedgehog::Hedgehog(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Hedgehog", "刺猬", "受到伤害时对敌人造成等量伤害", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillHedgehog>());
}

Kangaroo::Kangaroo(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Kangaroo", "袋鼠", "前方的友方+1HP/+1ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillKangaroo>());
}

Peacock::Peacock(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Peacock", "孔雀", "受到攻击+1ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillPeacock>());
}

Camel::Camel(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Camel", "骆驼", "受到攻击给后面最近的朋友+2HP/+2ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillCamel>());
}

Dodo::Dodo(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Dodo", "渡渡鸟", "战斗开始前给予前方最近队友50%ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillDodo>());
}

Blowfish::Blowfish(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Blowfish", "河豚", "受到伤害对一个随机敌人造成ATK", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillBlowfish>());
}

Skunk::Skunk(int hp, int attack, int ownerPlayer, int tier)
    : Pet("Skunk", "臭鼬", "战斗开始前将最高血量的敌人减少1/3HP", hp, attack, ownerPlayer, tier)
{
    setSkill(std::make_unique<SkillSkunk>());
}

// 实现派生类的拷贝构造函数
Cat::Cat(const Cat& other) : Pet(other) {}

Ant::Ant(const Ant& other) : Pet(other) {}

Fish::Fish(const Fish& other) : Pet(other) {}

Cricket::Cricket(const Cricket& other) : Pet(other) {}

Duck::Duck(const Duck& other) : Pet(other) {}

Swan::Swan(const Swan& other) : Pet(other) {}

Flamingo::Flamingo(const Flamingo& other) : Pet(other) {}

Hedgehog::Hedgehog(const Hedgehog& other) : Pet(other) {}

Kangaroo::Kangaroo(const Kangaroo& other) : Pet(other) {}

Peacock::Peacock(const Peacock& other) : Pet(other) {}

Camel::Camel(const Camel& other) : Pet(other) {}

Dodo::Dodo(const Dodo& other) : Pet(other) {}

Blowfish::Blowfish(const Blowfish& other) : Pet(other) {}

Skunk::Skunk(const Skunk& other) : Pet(other) {}

template <class Derived>
struct Registrar
{
    Registrar()
    {
        static_assert(std::is_base_of<Pet, Derived>::value, "Derived must inherit from Pet");
        Creator creator = []() -> std::unique_ptr<Pet> { return std::make_unique<Derived>(); };
        getAllPets().push_back(creator);
    };
};

// 所有 Pet 派生类全部在这里手动注册一次
static Registrar<Cat> catRegistrar;
static Registrar<Ant> antRegistrar;
static Registrar<Fish> fishRegistrar;
static Registrar<Cricket> cricketRegistrar;
static Registrar<Duck> duckRegistrar;
static Registrar<Swan> swanRegistrar;
static Registrar<Flamingo> flamingoRegistrar;
static Registrar<Hedgehog> hedgehogRegistrar;
static Registrar<Kangaroo> kangarooRegistrar;
static Registrar<Peacock> peacockRegistrar;
static Registrar<Camel> camelRegistrar;
static Registrar<Dodo> dodoRegistrar;
static Registrar<Blowfish> BlowfishRegistrar;
static Registrar<Skunk> skunkRegistrar;
