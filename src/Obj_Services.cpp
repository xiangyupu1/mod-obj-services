/*
** Written by MtgCore
** Rewritten by Poszer & Talamortis https://github.com/poszer/ & https://github.com/talamortis/
** AzerothCore 2019 http://www.azerothcore.org/
** Cleaned and made into a module by Micrah https://github.com/milestorme/
*/

#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Unit.h"
#include "Chat.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "SpellMgr.h"

/*enum gossicon
{
    GOSSIP_ICON_CHAT = 0,
    GOSSIP_ICON_VENDOR = 1,
    GOSSIP_ICON_TAXI = 2,
    GOSSIP_ICON_TRAINER = 3,
    GOSSIP_ICON_INTERACT_1 = 4,
    GOSSIP_ICON_INTERACT_2 = 5,
    GOSSIP_ICON_MONEY_BAG = 6,
    GOSSIP_ICON_TALK = 7,
    GOSSIP_ICON_TABARD = 8,
    GOSSIP_ICON_BATTLE = 9,
    GOSSIP_ICON_DOT = 10,
};*/

class Obj_Services : public ItemScript
{
public:
    Obj_Services() : ItemScript("MyObj_Services") { }
    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        if (player->IsInCombat())
        {
            player->CastSpell(player, 8690, false);
            //player->RemoveSpellCooldown(8690, true);
            return true;
        }
        else
        {
            return addmenu(player, item);
        }

    }
    void OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action)
    {
        ClearGossipMenuFor(player);
        CloseGossipMenuFor(player);
        switch (action)
        {
        case 10:
            addmenu(player, item);
            break;
        case 1:

            if (player->IsInCombat())
            {
                player->CastSpell(player, 8690, false);
                //player->RemoveSpellCooldown(8690, true);
            }
            else
            {
                player->CastSpell(player, 8690, true);
                player->RemoveSpellCooldown(8690, true);
            }
            break;
        case 2:
            AddGossipItemFor(player, 9, "[城市]主要城市 ", GOSSIP_SENDER_MAIN, 1001);
            AddGossipItemFor(player, 9, "[出生]种族出生地", GOSSIP_SENDER_MAIN, 1002);
            AddGossipItemFor(player, 9, "[野外]东部王国", GOSSIP_SENDER_MAIN, 1003);
            AddGossipItemFor(player, 9, "[野外]卡利姆多", GOSSIP_SENDER_MAIN, 1004);
            AddGossipItemFor(player, 9, "[野外]外域", GOSSIP_SENDER_MAIN, 1005);
            AddGossipItemFor(player, 9, "[野外]诺森德", GOSSIP_SENDER_MAIN, 1006);
            //AddGossipItemFor(player, 9, "竞技场传送", GOSSIP_SENDER_MAIN, 1007);
            AddGossipItemFor(player, 9, "传送到职业训练", GOSSIP_SENDER_MAIN, 1011);
            AddGossipItemFor(player, 9, "传送到技能训练|cFF006400[武器/骑术/飞行]|r", GOSSIP_SENDER_MAIN, 1012);
            AddGossipItemFor(player, 9, "【5人】经典旧世界地下城", GOSSIP_SENDER_MAIN, 1007);
            AddGossipItemFor(player, 9, "【5人】燃烧的远征地下城", GOSSIP_SENDER_MAIN, 1008);
            AddGossipItemFor(player, 9, "【5人】巫妖王之怒地下城", GOSSIP_SENDER_MAIN, 1009);
            AddGossipItemFor(player, 9, "【10人-40人】团队地下城", GOSSIP_SENDER_MAIN, 1010);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 3:
            if (player->HasAura(15007))
            {
                player->RemoveAurasDueToSpell(15007);
                player->ModifyMoney(-20000);
                ChatHandler(player->GetSession()).SendSysMessage("你的身上的复活虚弱状态已经被移除。");
            }
            else
            {
                ChatHandler(player->GetSession()).SendSysMessage("你的身上没有复活虚弱状态。");
            }
            break;
        case 5:
            if (player->HasSpell(34091) | player->HasSpell(34090) | player->HasSpell(33391))
            {
                ChatHandler(player->GetSession()).SendSysMessage("你已学会更高级的骑术。");
            }
            else {
                player->learnSpell(33388);
                player->learnSpell(33391);
                ChatHandler(player->GetSession()).SendSysMessage("已经学会中级骑术");
            }
            break;
        case 6:

            // ChatHandler(player->GetSession()).SendSysMessage(std::to_string(player->GetItemCount(37742)));
            AddGossipItemFor(player, 9, "现有|cFFFFFF00                     " + std::to_string(player->GetItemCount(37742)) + "积分", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, 9, "转换阵营              |cFFFFFF00200积分", GOSSIP_SENDER_MAIN, 6001, "是否花200积分转换阵营", 0, false);
            AddGossipItemFor(player, 9, "直升80                  |cFFFFFF0020积分", GOSSIP_SENDER_MAIN, 6002);
            AddGossipItemFor(player, 9, "【初级专业学习】|cFFFFFF0030积分", GOSSIP_SENDER_MAIN, 6003);
            AddGossipItemFor(player, 9, "【专业升级】       |cFFFFFF0030积分", GOSSIP_SENDER_MAIN, 6004);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;

        case 1001://主城传送菜单
            if (player->GetTeamId()) {
                AddGossipItemFor(player, 9, "奥格瑞玛", GOSSIP_SENDER_MAIN, 100105);
                AddGossipItemFor(player, 9, "幽暗城", GOSSIP_SENDER_MAIN, 100106);
                AddGossipItemFor(player, 9, "雷霆崖", GOSSIP_SENDER_MAIN, 100107);
                AddGossipItemFor(player, 9, "银月城", GOSSIP_SENDER_MAIN, 100108);
            }
            else
            {
                AddGossipItemFor(player, 9, "暴风城", GOSSIP_SENDER_MAIN, 100101);
                AddGossipItemFor(player, 9, "铁炉堡", GOSSIP_SENDER_MAIN, 100102);
                AddGossipItemFor(player, 9, "达纳苏斯", GOSSIP_SENDER_MAIN, 100103);
                AddGossipItemFor(player, 9, "埃索达", GOSSIP_SENDER_MAIN, 100104);
            }
            AddGossipItemFor(player, 9, "|cFF0000FF[外域]|r沙塔斯", GOSSIP_SENDER_MAIN, 100109);
            AddGossipItemFor(player, 9, "|cFF4B0082[诺森德]|r达拉然", GOSSIP_SENDER_MAIN, 100110);
            AddGossipItemFor(player, 9, "|cFF006400[中立]|r藏宝海湾", GOSSIP_SENDER_MAIN, 100111);
            AddGossipItemFor(player, 9, "|cFF006400[中立]|r棘齿城", GOSSIP_SENDER_MAIN, 100112);
            AddGossipItemFor(player, 9, "|cFF006400[中立]|r加基森", GOSSIP_SENDER_MAIN, 100114);
            AddGossipItemFor(player, 9, "|cFF006400[中立]|r永望镇", GOSSIP_SENDER_MAIN, 100113);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100101:
            TP(player, 0, -8832.833, 633.1505, 94.2408, 1.70201);
            break;
        case 100102:
            TP(player, 0, -4926.76, -949.64, 501.559, 2.24414);
            break;
        case 100103:
            TP(player, 1, 9869.91, 2493.58, 1315.88, 2.78897);
            break;
        case 100104:
            TP(player, 530, -3864.92, -11643.7, -137.644, 5.50862);
            break;
        case 100105:
            TP(player, 1, 1601.08, -4378.69, 9.9846, 2.14362);
            break;
        case 100106:
            TP(player, 0, 1633.75, 240.167, -43.1034, 6.26128);
            break;
        case 100107:
            TP(player, 1, -1274.45, 71.8601, 128.159, 2.80623);
            break;
        case 100108: //银月城
            TP(player, 530, 9738.28, -7454.19, 13.5605, 0.043914);
            break;
        case 100109:
            TP(player, 530, -1887.62, 5359.09, -12.4279, 4.40435);
            break;
        case 100110:
            TP(player, 571, 5809.55, 503.975, 657.526, 2.38338);
            break;
        case 100111:
            TP(player, 0, -14281.9, 552.564, 8.90422, 0.860144);
            break;
        case 100112:
            TP(player, 1, -955.219, -3678.92, 8.29946, 0);
            break;
        case 100113:
            TP(player, 1, 6724.58, -4609.16, 720.597, 4.87852);
            break;
        case 100114:
            TP(player, 1, -7122.8, -3704.82, 14.0526, 0);
            break;


        case 1002://各种族出生地
            if (player->GetTeamId())
            {
                AddGossipItemFor(player, 9, "兽人出生地", GOSSIP_SENDER_MAIN, 100206);
                AddGossipItemFor(player, 9, "巨魔出生地", GOSSIP_SENDER_MAIN, 100207);
                AddGossipItemFor(player, 9, "牛头人出生地", GOSSIP_SENDER_MAIN, 100208);
                AddGossipItemFor(player, 9, "亡灵出生地", GOSSIP_SENDER_MAIN, 100209);
                AddGossipItemFor(player, 9, "血精灵出生地", GOSSIP_SENDER_MAIN, 100210);
            }
            else
            {
                AddGossipItemFor(player, 9, "人类出生地", GOSSIP_SENDER_MAIN, 100201);
                AddGossipItemFor(player, 9, "矮人出生地", GOSSIP_SENDER_MAIN, 100202);
                AddGossipItemFor(player, 9, "侏儒出生地", GOSSIP_SENDER_MAIN, 100203);
                AddGossipItemFor(player, 9, "暗夜精灵出生地", GOSSIP_SENDER_MAIN, 100204);
                AddGossipItemFor(player, 9, "德莱尼出生地", GOSSIP_SENDER_MAIN, 100205);
            }
            AddGossipItemFor(player, 9, "|cFF006400死亡骑士出生地|r", GOSSIP_SENDER_MAIN, 100211);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100201:
            TP(player, 0, -8949.95, -132.493, 83.5312, 0);
            break;
        case 100202:
            TP(player, 0, -6240.32, 331.033, 382.758, 6.1);
            break;
        case 100203:
            TP(player, 0, -6240, 331, 383, 0);
            break;
        case 100204:
            TP(player, 1, 10311.3, 832.463, 1326.41, 5.6);
            break;
        case 100205:
            TP(player, 530, -3961.64, -13931.2, 100.615, 2);
            break;
        case 100206:
            TP(player, 1, -618.518, -4251.67, 38.718, 0);
            break;
        case 100207:
            TP(player, 1, -618.518, -4251.67, 38.7, 4.747);
            break;
        case 100208:
            TP(player, 1, -2917.58, -257.98, 52.9968, 0);
            break;
        case 100209://亡灵
            TP(player, 0, 1676.71, 1678.31, 121.67, 2.70526);
            break;
        case 100210:
            TP(player, 530, 10349.6, -6357.29, 33.4026, 5.31605);
            break;
        case 100211:
            TP(player, 609, 2355.84, -5664.77, 426.028, 3.65997);
            break;
        case 1003://东部王国
            AddGossipItemFor(player, 9, "艾尔文森林", GOSSIP_SENDER_MAIN, 100301);
            AddGossipItemFor(player, 9, "永歌森林", GOSSIP_SENDER_MAIN, 100302);
            AddGossipItemFor(player, 9, "丹莫罗", GOSSIP_SENDER_MAIN, 100303);
            AddGossipItemFor(player, 9, "提瑞斯法林地", GOSSIP_SENDER_MAIN, 100304);
            AddGossipItemFor(player, 9, "洛克莫丹", GOSSIP_SENDER_MAIN, 100305);
            AddGossipItemFor(player, 9, "幽魂之地", GOSSIP_SENDER_MAIN, 100306);
            AddGossipItemFor(player, 9, "西部荒野", GOSSIP_SENDER_MAIN, 100307);
            AddGossipItemFor(player, 9, "银松森林", GOSSIP_SENDER_MAIN, 100308);
            AddGossipItemFor(player, 9, "赤脊山", GOSSIP_SENDER_MAIN, 100309);
            AddGossipItemFor(player, 9, "暮色森林", GOSSIP_SENDER_MAIN, 100310);
            AddGossipItemFor(player, 9, "湿地", GOSSIP_SENDER_MAIN, 100311);
            AddGossipItemFor(player, 9, "希尔斯布莱德丘陵", GOSSIP_SENDER_MAIN, 100312);
            AddGossipItemFor(player, 9, "奥特兰克山脉", GOSSIP_SENDER_MAIN, 100313);
            AddGossipItemFor(player, 9, "阿拉希高地", GOSSIP_SENDER_MAIN, 100314);
            AddGossipItemFor(player, 9, "荆棘谷", GOSSIP_SENDER_MAIN, 100315);
            AddGossipItemFor(player, 9, "荒芜之地", GOSSIP_SENDER_MAIN, 100316);
            AddGossipItemFor(player, 9, "悲伤沼泽", GOSSIP_SENDER_MAIN, 100317);
            AddGossipItemFor(player, 9, "辛特兰", GOSSIP_SENDER_MAIN, 100318);
            AddGossipItemFor(player, 9, "灼热峡谷", GOSSIP_SENDER_MAIN, 100319);
            AddGossipItemFor(player, 9, "诅咒之地", GOSSIP_SENDER_MAIN, 100320);
            AddGossipItemFor(player, 9, "燃烧平原", GOSSIP_SENDER_MAIN, 100321);
            AddGossipItemFor(player, 9, "西瘟疫之地", GOSSIP_SENDER_MAIN, 100322);
            AddGossipItemFor(player, 9, "东瘟疫之地", GOSSIP_SENDER_MAIN, 100323);
            AddGossipItemFor(player, 9, "奎尔丹纳斯岛", GOSSIP_SENDER_MAIN, 100324);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100301:TP(player, 0, -9449.06, 64.8392, 56.3581, 3.0704); break;
        case 100302:TP(player, 530, 9024.37, -6682.55, 16.8973, 3.1413); break;
        case 100303:TP(player, 0, -5603.76, -482.704, 396.98, 5.2349); break;
        case 100304:TP(player, 0, 2274.95, 323.918, 34.1137, 4.2436); break;
        case 100305:TP(player, 0, -5405.85, -2894.15, 341.972, 5.4823); break;
        case 100306:TP(player, 530, 7595.73, -6819.6, 84.3718, 2.5656); break;
        case 100307:TP(player, 0, -10684.9, 1033.63, 32.5389, 6.0738); break;
        case 100308:TP(player, 0, 505.126, 1504.63, 124.808, 1.7798); break;
        case 100309:TP(player, 0, -9447.8, -2270.85, 71.8224, 0.28385); break;
        case 100310:TP(player, 0, -10531.7, -1281.91, 38.8647, 1.5695); break;
        case 100311:TP(player, 0, -3517.75, -913.401, 8.86625, 2.607); break;
        case 100312:TP(player, 0, -385.805, -787.954, 54.6655, 1.0392); break;
        case 100313:TP(player, 0, 275.049, -652.044, 130.296, 0.50203); break;
        case 100314:TP(player, 0, -1581.45, -2704.06, 35.4168, 0.490373); break;
        case 100315:TP(player, 0, -11921.7, -59.544, 39.7262, 3.7357); break;
        case 100316:TP(player, 0, -6782.56, -3128.14, 240.48, 5.6591); break;
        case 100317:TP(player, 0, -10368.6, -2731.3, 21.6537, 5.2923); break;
        case 100318:TP(player, 0, 112.406, -3929.74, 136.358, 0.981903); break;
        case 100319:TP(player, 0, -6686.33, -1198.55, 240.027, 0.91688); break;
        case 100320:TP(player, 0, -11184.7, -3019.31, 7.29238, 3.20542); break;
        case 100321:TP(player, 0, -7979.78, -2105.72, 127.919, 5.10148); break;
        case 100322:TP(player, 0, 1743.69, -1723.86, 59.6648, 5.23722); break;
        case 100323:TP(player, 0, 2280.64, -5275.05, 82.0166, 4.747); break;
        case 100324:TP(player, 530, 12806.5, -6911.11, 41.1156, 2.2293); break;
        case 1004://卡利姆多
            AddGossipItemFor(player, 9, "秘蓝岛", GOSSIP_SENDER_MAIN, 100401);
            AddGossipItemFor(player, 9, "秘血岛", GOSSIP_SENDER_MAIN, 100402);
            AddGossipItemFor(player, 9, "泰达希尔", GOSSIP_SENDER_MAIN, 100403);
            AddGossipItemFor(player, 9, "杜隆塔尔", GOSSIP_SENDER_MAIN, 100404);
            AddGossipItemFor(player, 9, "莫高雷", GOSSIP_SENDER_MAIN, 100405);
            AddGossipItemFor(player, 9, "黑海岸", GOSSIP_SENDER_MAIN, 100406);
            AddGossipItemFor(player, 9, "贫瘠之地", GOSSIP_SENDER_MAIN, 100407);
            AddGossipItemFor(player, 9, "石爪山脉", GOSSIP_SENDER_MAIN, 100408);
            AddGossipItemFor(player, 9, "灰谷森林", GOSSIP_SENDER_MAIN, 100409);
            AddGossipItemFor(player, 9, "千针石林", GOSSIP_SENDER_MAIN, 100410);
            AddGossipItemFor(player, 9, "凄凉之地", GOSSIP_SENDER_MAIN, 100411);
            AddGossipItemFor(player, 9, "尘泥沼泽", GOSSIP_SENDER_MAIN, 100412);
            AddGossipItemFor(player, 9, "菲拉斯", GOSSIP_SENDER_MAIN, 100413);
            AddGossipItemFor(player, 9, "塔纳利斯沙漠", GOSSIP_SENDER_MAIN, 100414);
            AddGossipItemFor(player, 9, "艾萨拉", GOSSIP_SENDER_MAIN, 100415);
            AddGossipItemFor(player, 9, "费伍德森林", GOSSIP_SENDER_MAIN, 100416);
            AddGossipItemFor(player, 9, "安戈洛环形山", GOSSIP_SENDER_MAIN, 100417);
            AddGossipItemFor(player, 9, "希利苏斯", GOSSIP_SENDER_MAIN, 100418);
            AddGossipItemFor(player, 9, "冬泉谷", GOSSIP_SENDER_MAIN, 100419);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100401:TP(player, 530, -4192.62, -12576.7, 36.7598, 1.62813); break;
        case 100402:TP(player, 530, -2095.7, -11841.1, 51.1557, 6.19288); break;
        case 100403:TP(player, 1, 9889.03, 915.869, 1307.43, 1.9336); break;
        case 100404:TP(player, 1, 228.978, -4741.87, 10.1027, 0.416883); break;
        case 100405:TP(player, 1, -2473.87, -501.225, -9.42465, 0.6525); break;
        case 100406:TP(player, 1, 6463.25, 683.986, 8.92792, 4.33534); break;
        case 100407:TP(player, 1, -1028.95, -2462.17, 91.6679, 5.83412); break;
        case 100408:TP(player, 1, 1574.89, 1031.57, 137.442, 3.8013); break;
        case 100409:TP(player, 1, 1919.77, -2169.68, 94.6729, 6.14177); break;
        case 100410:TP(player, 1, -5375.53, -2509.2, -40.432, 2.41885); break;
        case 100411:TP(player, 1, -656.056, 1510.12, 88.3746, 3.29553); break;
        case 100412:TP(player, 1, -3350.12, -3064.85, 33.0364, 5.12666); break;
        case 100413:TP(player, 1, -4808.31, 1040.51, 103.769, 2.90655); break;
        case 100414:TP(player, 1, -6940.91, -3725.7, 48.9381, 3.11174); break;
        case 100415:TP(player, 1, 3117.12, -4387.97, 91.9059, 5.49897); break;
        case 100416:TP(player, 1, 3898.8, -1283.33, 220.519, 6.24307); break;
        case 100417:TP(player, 1, -6291.55, -1158.62, -258.138, 0.457099); break;
        case 100418:TP(player, 1, -6815.25, 730.015, 40.9483, 2.39066); break;
        case 100419:TP(player, 1, 6658.57, -4553.48, 718.019, 5.18088); break;
        case 1005://沙塔斯
            AddGossipItemFor(player, 9, "地狱火半岛", GOSSIP_SENDER_MAIN, 100501);
            if (!player->GetTeamId())
            {
                AddGossipItemFor(player, 9, "地狱火半岛-荣耀堡", GOSSIP_SENDER_MAIN, 100502);
            }
            else {
                AddGossipItemFor(player, 9, "地狱火半岛-萨尔玛", GOSSIP_SENDER_MAIN, 100503);
            }
            AddGossipItemFor(player, 9, "赞加沼泽", GOSSIP_SENDER_MAIN, 100504);
            AddGossipItemFor(player, 9, "泰罗卡森林", GOSSIP_SENDER_MAIN, 100505);
            AddGossipItemFor(player, 9, "纳格兰", GOSSIP_SENDER_MAIN, 100506);
            AddGossipItemFor(player, 9, "刀锋山", GOSSIP_SENDER_MAIN, 100507);
            AddGossipItemFor(player, 9, "虚空风暴", GOSSIP_SENDER_MAIN, 100508);
            AddGossipItemFor(player, 9, "影月谷", GOSSIP_SENDER_MAIN, 100509);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100501:TP(player, 530, -207.335, 2035.92, 96.464, 1.59676); break;
        case 100502:TP(player, 530, -683.05, 2657.57, 91.04, 1); break;
        case 100503:TP(player, 530, 139.96, 2671.51, 85.509, 1); break;
        case 100504:TP(player, 530, -220.297, 5378.58, 23.3223, 1.61718); break;
        case 100505:TP(player, 530, -2266.23, 4244.73, 1.47728, 3.68426); break;
        case 100506:TP(player, 530, -1610.85, 7733.62, -17.2773, 1.33522); break;
        case 100507:TP(player, 530, 2029.75, 6232.07, 133.495, 1.30395); break;
        case 100508:TP(player, 530, 3271.2, 3811.61, 143.153, 3.44101); break;
        case 100509:TP(player, 530, -3681.01, 2350.76, 76.587, 4.25995); break;

        case 1006://诺森德
            AddGossipItemFor(player, 9, "北风苔原", GOSSIP_SENDER_MAIN, 100601);
            AddGossipItemFor(player, 9, "凛风峡湾", GOSSIP_SENDER_MAIN, 100602);
            AddGossipItemFor(player, 9, "龙骨荒野", GOSSIP_SENDER_MAIN, 100603);
            AddGossipItemFor(player, 9, "灰熊丘陵", GOSSIP_SENDER_MAIN, 100604);
            AddGossipItemFor(player, 9, "祖达克", GOSSIP_SENDER_MAIN, 100605);
            AddGossipItemFor(player, 9, "索拉查盆地", GOSSIP_SENDER_MAIN, 100606);
            AddGossipItemFor(player, 9, "水晶之歌森林", GOSSIP_SENDER_MAIN, 100607);
            AddGossipItemFor(player, 9, "风暴峭壁", GOSSIP_SENDER_MAIN, 100608);
            AddGossipItemFor(player, 9, "冰冠冰川", GOSSIP_SENDER_MAIN, 100609);
            AddGossipItemFor(player, 9, "冬拥湖", GOSSIP_SENDER_MAIN, 100610);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100601:TP(player, 571, 2954.24, 5379.13, 60.4538, 2.55544); break;
        case 100602:TP(player, 571, 682.848, -3978.3, 230.161, 1.54207); break;
        case 100603:TP(player, 571, 2678.17, 891.826, 4.37494, 0.101121); break;
        case 100604:TP(player, 571, 4017.35, -3403.85, 290, 5.35431); break;
        case 100605:TP(player, 571, 5560.23, -3211.66, 371.709, 5.55055); break;
        case 100606:TP(player, 571, 5614.67, 5818.86, -69.722, 3.60807); break;
        case 100607:TP(player, 571, 5411.17, -966.37, 167.082, 1.57167); break;
        case 100608:TP(player, 571, 6120.46, -1013.89, 408.39, 5.12322); break;
        case 100609:TP(player, 571, 8323.28, 2763.5, 655.093, 2.87223); break;
        case 100610:TP(player, 571, 4522.23, 2828.01, 389.975, 0.215009); break;

        case 1007://经典旧世界地下城
            AddGossipItemFor(player, 9, "怒焰裂谷", GOSSIP_SENDER_MAIN, 100701);
            AddGossipItemFor(player, 9, "死亡矿井", GOSSIP_SENDER_MAIN, 100702);
            AddGossipItemFor(player, 9, "哀嚎洞穴", GOSSIP_SENDER_MAIN, 100703);
            AddGossipItemFor(player, 9, "影牙城堡", GOSSIP_SENDER_MAIN, 100704);
            AddGossipItemFor(player, 9, "暴风城监狱", GOSSIP_SENDER_MAIN, 100705);
            AddGossipItemFor(player, 9, "剃刀沼泽", GOSSIP_SENDER_MAIN, 100706);
            AddGossipItemFor(player, 9, "黑暗深渊", GOSSIP_SENDER_MAIN, 100707);
            AddGossipItemFor(player, 9, "诺莫瑞根", GOSSIP_SENDER_MAIN, 100708);
            AddGossipItemFor(player, 9, "血色修道院", GOSSIP_SENDER_MAIN, 100709);
            AddGossipItemFor(player, 9, "剃刀高地", GOSSIP_SENDER_MAIN, 100710);
            AddGossipItemFor(player, 9, "奥达曼", GOSSIP_SENDER_MAIN, 100711);
            AddGossipItemFor(player, 9, "玛拉顿", GOSSIP_SENDER_MAIN, 100712);
            AddGossipItemFor(player, 9, "祖尔法拉克", GOSSIP_SENDER_MAIN, 100713);
            AddGossipItemFor(player, 9, "沉没的神庙", GOSSIP_SENDER_MAIN, 100714);
            AddGossipItemFor(player, 9, "黑石深渊", GOSSIP_SENDER_MAIN, 100715);
            AddGossipItemFor(player, 9, "黑石塔", GOSSIP_SENDER_MAIN, 100716);
            AddGossipItemFor(player, 9, "厄运之槌", GOSSIP_SENDER_MAIN, 100717);
            AddGossipItemFor(player, 9, "通灵学院", GOSSIP_SENDER_MAIN, 100718);
            AddGossipItemFor(player, 9, "斯坦索姆", GOSSIP_SENDER_MAIN, 100719);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100701:TP(player, 1, 1811.78, -4410.5, -18.4704, 5.20165); break;
        case 100702:TP(player, 0, -11209.6, 1666.54, 24.6974, 1.42053); break;
        case 100703:TP(player, 1, -731.607, -2218.39, 17.0281, 2.78486); break;
        case 100704:TP(player, 0, -234.675, 1561.63, 76.8921, 1.24031); break;
        case 100705:TP(player, 0, -8799.15, 832.718, 97.6348, 6.04085); break;
        case 100706:TP(player, 1, -4470.28, -1677.77, 81.3925, 1.16302); break;
        case 100707:TP(player, 1, 4249.99, 740.102, -25.671, 1.34062); break;
        case 100708:TP(player, 0, -5163.54, 925.423, 257.181, 1.57423); break;
        case 100709:TP(player, 0, 2873.15, -764.523, 160.332, 5.10447); break;
        case 100710:TP(player, 1, -4657.3, -2519.35, 81.0529, 4.54808); break;
        case 100711:TP(player, 0, -6071.37, -2955.16, 209.782, 0.015708); break;
        case 100712:TP(player, 1, -1421.42, 2907.83, 137.415, 1.70718); break;
        case 100713:TP(player, 1, -6801.19, -2893.02, 9.00388, 0.158639); break;
        case 100714:TP(player, 0, -10177.9, -3994.9, -111.239, 6.01885); break;
        case 100715:TP(player, 0, -7179.34, -921.212, 165.821, 5.09599); break;
        case 100716:TP(player, 0, -7527.05, -1226.77, 285.732, 5.29626); break;
        case 100717:TP(player, 1, -3520.14, 1119.38, 161.025, 4.70454); break;
        case 100718:TP(player, 0, 1269.64, -2556.21, 93.6088, 0.620623); break;
        case 100719:TP(player, 0, 3352.92, -3379.03, 144.782, 6.25978); break;

        case 1008://燃烧的远征地下城
            AddGossipItemFor(player, 9, "|cFF0000FF地狱火堡垒[地狱火城墙]|r", GOSSIP_SENDER_MAIN, 100801);
            AddGossipItemFor(player, 9, "|cFF0000FF地狱火堡垒[鲜血熔炉]|r", GOSSIP_SENDER_MAIN, 100802);
            AddGossipItemFor(player, 9, "|cFF0000FF地狱火堡垒[破碎大厅]|r", GOSSIP_SENDER_MAIN, 100803);
            AddGossipItemFor(player, 9, "|cFF0000FF盘牙水库[奴隶围栏]|r", GOSSIP_SENDER_MAIN, 100804);
            AddGossipItemFor(player, 9, "|cFF0000FF盘牙水库[幽暗沼泽]|r", GOSSIP_SENDER_MAIN, 100805);
            AddGossipItemFor(player, 9, "|cFF0000FF盘牙水库[蒸汽地窟]|r", GOSSIP_SENDER_MAIN, 100806);
            AddGossipItemFor(player, 9, "|cFF0000FF奥金顿[塞泰克大厅]|r", GOSSIP_SENDER_MAIN, 100807);
            AddGossipItemFor(player, 9, "|cFF0000FF奥金顿[法力陵墓]|r", GOSSIP_SENDER_MAIN, 100808);
            AddGossipItemFor(player, 9, "|cFF0000FF奥金顿[奥金尼地穴]|r", GOSSIP_SENDER_MAIN, 100809);
            AddGossipItemFor(player, 9, "|cFF4B0082奥金顿[暗影迷宫]|r", GOSSIP_SENDER_MAIN, 100810);
            AddGossipItemFor(player, 9, "|cFF4B0082时光之穴[黑色沼泽]|r", GOSSIP_SENDER_MAIN, 100811);
            AddGossipItemFor(player, 9, "|cFF4B0082时光之穴[旧希尔斯布莱德丘陵]|r", GOSSIP_SENDER_MAIN, 100812);
            AddGossipItemFor(player, 9, "|cFF4B0082风暴要塞[禁魔监狱]|r", GOSSIP_SENDER_MAIN, 100813);
            AddGossipItemFor(player, 9, "|cFF4B0082风暴要塞[生态船]|r", GOSSIP_SENDER_MAIN, 100814);
            AddGossipItemFor(player, 9, "|cFF4B0082风暴要塞[能源舰]|r", GOSSIP_SENDER_MAIN, 100815);
            AddGossipItemFor(player, 9, "|cFF4B0082魔导师平台|r", GOSSIP_SENDER_MAIN, 100816);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100801:TP(player, 530, -360.671, 3071.9, -15.1, 1.883); break;
        case 100802:TP(player, 530, -296.487, 3154.6098, 31.617, 2.24); break;
        case 100803:TP(player, 530, -308.05, 3066.98, -3.018, 1.76); break;
        case 100804:TP(player, 530, 727.828, 7011.997, -71.861, 0.245473); break;
        case 100805:TP(player, 530, 777.089, 6763.45, -72.066, 5.03985); break;
        case 100806:TP(player, 530, 817.459, 6934.923, -80.624, 1.51974); break;
        case 100807:TP(player, 530, -3362.165, 4826.771, -101.396, 4.73); break;
        case 100808:TP(player, 530, -3243.83, 4942.69, -101.364, 0); break;
        case 100809:TP(player, 530, -3362.06, 5059.393, -101.396, 1.573); break;
        case 100810:TP(player, 530, -3494.912, 4943.865, -101.393, 3.125); break;
        case 100811:TP(player, 1, -8742.04, -4217.996, -209.5, 2.1); break;
        case 100812:TP(player, 1, -8391.215, -4064.293, -208.585, 0.199); break;
        case 100813:TP(player, 530, 3281.65, 1408.55, 502.413, 5.22); break;
        case 100814:TP(player, 530, 3351.35, 1530.116, 179.69, 5.63); break;
        case 100815:TP(player, 530, 2926.8, 1603.597, 249, 3.91); break;
        case 100816:TP(player, 530, 12884.6, -7317.69, 65.5023, 4.799); break;

        case 1009://巫妖王之怒地下城
            AddGossipItemFor(player, 9, "|cFF4B0082乌特加德城堡|r", GOSSIP_SENDER_MAIN, 100901);
            AddGossipItemFor(player, 9, "|cFF4B0082魔枢|r", GOSSIP_SENDER_MAIN, 100902);
            AddGossipItemFor(player, 9, "|cFF4B0082艾卓-尼鲁布|r", GOSSIP_SENDER_MAIN, 100903);
            AddGossipItemFor(player, 9, "|cFF4B0082达克萨隆要塞|r", GOSSIP_SENDER_MAIN, 100904);
            AddGossipItemFor(player, 9, "|cFF4B0082紫罗兰监狱|r", GOSSIP_SENDER_MAIN, 100905);
            AddGossipItemFor(player, 9, "|cFFB22222古达克|r", GOSSIP_SENDER_MAIN, 100906);
            AddGossipItemFor(player, 9, "|cFFB22222岩石大厅|r", GOSSIP_SENDER_MAIN, 100907);
            AddGossipItemFor(player, 9, "|cFFB22222净化斯坦索姆|r", GOSSIP_SENDER_MAIN, 100908);
            AddGossipItemFor(player, 9, "|cFFB22222闪电大厅|r", GOSSIP_SENDER_MAIN, 100909);
            AddGossipItemFor(player, 9, "|cFFB22222乌特加德之巅|r", GOSSIP_SENDER_MAIN, 100910);
            AddGossipItemFor(player, 9, "|cFFB22222冰封大殿|r[灵魂洪炉/映像大厅/萨隆矿坑]", GOSSIP_SENDER_MAIN, 100911);
            AddGossipItemFor(player, 9, "|cFFB22222冠军的试炼|r", GOSSIP_SENDER_MAIN, 100912);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 100901:TP(player, 571, 1203.41, -4868.59, 41.2486, 0.283237); break;
        case 100902:TP(player, 571, 3782.89, 6965.23, 105.088, 6.14194); break;
        case 100903:TP(player, 571, 3707.86, 2150.23, 36.76, 3.22); break;
        case 100904:TP(player, 571, 4765.59, -2038.24, 229.363, 0.887627); break;
        case 100905:TP(player, 571, 5693.08, 502.588, 652.672, 4.0229); break;
        case 100906:TP(player, 571, 6722.44, -4640.67, 450.632, 3.91123); break;
        case 100907:TP(player, 571, 8922.12, -1009.16, 1039.56, 1.57044); break;
        case 100908:TP(player, 1, -8756.39, -4440.68, -199.489, 4.66289); break;
        case 100909:TP(player, 571, 9136.52, -1311.81, 1066.29, 5.19113); break;
        case 100910:TP(player, 571, 1267.24, -4857.3, 215.764, 3.22768); break;
        case 100911:TP(player, 571, 5643.16, 2028.81, 798.274, 4.60242); break;
        case 100912:TP(player, 571, 8590.95, 791.792, 558.235, 3.13127); break;

        case 1010://团队地下城
            AddGossipItemFor(player, 9, "|cFF0000FF【20人】祖尔格拉布|r", GOSSIP_SENDER_MAIN, 101001);
            AddGossipItemFor(player, 9, "|cFF0000FF【20人】安其拉废墟|r", GOSSIP_SENDER_MAIN, 101002);
            AddGossipItemFor(player, 9, "|cFF0000FF【40人】熔火之心|r", GOSSIP_SENDER_MAIN, 101003);
            AddGossipItemFor(player, 9, "|cFF0000FF【40人】安其拉神殿|r", GOSSIP_SENDER_MAIN, 101004);
            AddGossipItemFor(player, 9, "|cFF0000FF【40人】黑翼之巢|r", GOSSIP_SENDER_MAIN, 101005);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】格鲁尔的巢穴|r", GOSSIP_SENDER_MAIN, 101006);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】玛瑟里顿的巢穴|r", GOSSIP_SENDER_MAIN, 101007);
            AddGossipItemFor(player, 9, "|cFF4B0082【10人】卡拉赞|r", GOSSIP_SENDER_MAIN, 101008);
            AddGossipItemFor(player, 9, "|cFF4B0082【10人】祖阿曼|r", GOSSIP_SENDER_MAIN, 101009);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】黑暗神殿|r", GOSSIP_SENDER_MAIN, 101010);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】海加尔山之巅|r", GOSSIP_SENDER_MAIN, 101011);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】毒蛇神殿|r", GOSSIP_SENDER_MAIN, 101012);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】太阳之井高地|r", GOSSIP_SENDER_MAIN, 101013);
            AddGossipItemFor(player, 9, "|cFF4B0082【25人】风暴要塞|r", GOSSIP_SENDER_MAIN, 101014);
            AddGossipItemFor(player, 9, "【10人/25人】十字军的试炼", GOSSIP_SENDER_MAIN, 101015);
            AddGossipItemFor(player, 9, "【10人/25人】冰冠堡垒", GOSSIP_SENDER_MAIN, 101016);
            AddGossipItemFor(player, 9, "【10人/25人】奥妮克希亚的巢穴", GOSSIP_SENDER_MAIN, 101017);
            AddGossipItemFor(player, 9, "【10人/25人】纳克萨玛斯", GOSSIP_SENDER_MAIN, 101018);
            AddGossipItemFor(player, 9, "【10人/25人】永恒之眼", GOSSIP_SENDER_MAIN, 101019);
            AddGossipItemFor(player, 9, "【10人/25人】奥杜尔", GOSSIP_SENDER_MAIN, 101020);
            AddGossipItemFor(player, 9, "【10人/25人】黑曜石圣殿", GOSSIP_SENDER_MAIN, 101021);
            AddGossipItemFor(player, 9, "【10人/25人】阿尔卡冯的宝库", GOSSIP_SENDER_MAIN, 101022);

            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 101001:TP(player, 0, -11916.7, -1215.72, 92.289, 4.72454); break;
        case 101002:TP(player, 1, -8409.82, 1499.06, 27.7179, 2.51868); break;
        case 101003:TP(player, 230, 1126.64, -459.94, -102.535, 3.46095); break;
        case 101004:TP(player, 1, -8240.09, 1991.32, 129.072, 0.941603); break;
        case 101005:TP(player, 229, 152.451, -474.881, 116.84, 0.001073); break;
        case 101006:TP(player, 530, 3530.06, 5104.08, 3.50861, 5.51117); break;
        case 101007:TP(player, 530, -336.411, 3130.46, -102.928, 5.20322); break;
        case 101008:TP(player, 0, -11105.9, -2000.33, 49.4819, 0.649895); break;
        case 101009:TP(player, 530, 6851.78, -7972.57, 179.242, 4.64691); break;
        case 101010:TP(player, 530, -3649.92, 317.469, 35.2827, 2.94285); break;
        case 101011:TP(player, 1, -8177.89, -4181.23, -167.552, 0.913338); break;
        case 101012:TP(player, 530, 797.855, 6865.77, -65.4165, 0.005938); break;
        case 101013:TP(player, 530, 12574.1, -6774.81, 15.0904, 3.13788); break;
        case 101014:TP(player, 530, 3088.49, 1381.57, 184.863, 4.61973); break;
        case 101015:TP(player, 571, 8515.61, 714.153, 558.248, 1.57753); break;
        case 101016:TP(player, 571, 5855.22, 2102.03, 635.991, 3.57899); break;
        case 101017:TP(player, 1, -4708.27, -3727.64, 54.5589, 3.72786); break;
        case 101018:TP(player, 571, 3668.72, -1262.46, 243.622, 4.785); break;
        case 101019:TP(player, 571, 3784.17, 7028.84, 161.258, 5.79993); break;
        case 101020:TP(player, 571, 9222.88, -1113.59, 1216.12, 6.27549); break;
        case 101021:TP(player, 571, 3472.43, 264.923, -120.146, 3.27923); break;
        case 101022:TP(player, 571, 5453.72, 2840.79, 421.28, 0.01); break;

        case 1011://职业技能训练师
            if (!player->GetTeamId())
            {
                AddGossipItemFor(player, 9, "战士训练师", GOSSIP_SENDER_MAIN, 101101);
                AddGossipItemFor(player, 9, "圣骑士训练师", GOSSIP_SENDER_MAIN, 101102);
                AddGossipItemFor(player, 9, "死亡骑士训练师", GOSSIP_SENDER_MAIN, 101103);
                AddGossipItemFor(player, 9, "萨满训练师", GOSSIP_SENDER_MAIN, 101104);
                AddGossipItemFor(player, 9, "猎人训练师", GOSSIP_SENDER_MAIN, 101105);
                AddGossipItemFor(player, 9, "德鲁伊训练师", GOSSIP_SENDER_MAIN, 101106);
                AddGossipItemFor(player, 9, "盗贼训练师", GOSSIP_SENDER_MAIN, 101107);
                AddGossipItemFor(player, 9, "法师训练师", GOSSIP_SENDER_MAIN, 101108);
                AddGossipItemFor(player, 9, "术士训练师", GOSSIP_SENDER_MAIN, 101109);
                AddGossipItemFor(player, 9, "牧师训练师", GOSSIP_SENDER_MAIN, 101110);
            }
            else
            {
                AddGossipItemFor(player, 9, "战士训练师", GOSSIP_SENDER_MAIN, 101111);
                AddGossipItemFor(player, 9, "圣骑士训练师", GOSSIP_SENDER_MAIN, 101112);
                AddGossipItemFor(player, 9, "死亡骑士训练师", GOSSIP_SENDER_MAIN, 101113);
                AddGossipItemFor(player, 9, "萨满训练师", GOSSIP_SENDER_MAIN, 101114);
                AddGossipItemFor(player, 9, "猎人训练师", GOSSIP_SENDER_MAIN, 101115);
                AddGossipItemFor(player, 9, "德鲁伊训练师", GOSSIP_SENDER_MAIN, 101116);
                AddGossipItemFor(player, 9, "盗贼训练师", GOSSIP_SENDER_MAIN, 101117);
                AddGossipItemFor(player, 9, "法师训练师", GOSSIP_SENDER_MAIN, 101118);
                AddGossipItemFor(player, 9, "术士训练师", GOSSIP_SENDER_MAIN, 101119);
                AddGossipItemFor(player, 9, "牧师训练师", GOSSIP_SENDER_MAIN, 101120);
            }
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 101101:TP(player, 0, -8682.700195, 322.091125, 109.437958, 0); break;
        case 101102:TP(player, 0, -8573.793945, 877.343018, 106.51931, 0); break;
        case 101103:TP(player, 0, 2365.21, -5658.35, 426.06, 0); break;
        case 101104:TP(player, 0, -9032.573242, 545.84259, 72.16095, 0); break;
        case 101105:TP(player, 0, -8422.097656, 550.078674, 95.44873, 0); break;
        case 101106:TP(player, 1, 7870.23, -2586.97, 486.95, 0); break;
        case 101107:TP(player, 0, -8751.876953, 381.32193, 101.056236, 0); break;
        case 101108:TP(player, 0, -9009.386719, 875.746765, 29.621387, 0); break;
        case 101109:TP(player, 0, -8972.834961, 1027.723511, 101.40416, 0); break;
        case 101110:TP(player, 0, -8517.649414, 858.083801, 109.81385, 0); break;
        case 101111:TP(player, 1, 1971.24, -4805.08, 56.99, 0); break;
        case 101112:TP(player, 1, 1936.14, -4138.31, 41.03, 0); break;
        case 101113:TP(player, 0, 2365.21, -5658.35, 426.06, 0); break;
        case 101114:TP(player, 1, 1928.482, -4228.17, 42.3219, 0); break;
        case 101115:TP(player, 1, 2135.33, -4610.78, 54.3865, 0); break;
        case 101116:TP(player, 1, 7870.23, -2586.97, 486.95, 0); break;
        case 101117:TP(player, 1, 1776.47, -4285.65, 7.44, 0); break;
        case 101118:TP(player, 1, 1468.58, -4221.86, 59.22, 0); break;
        case 101119:TP(player, 1, 1838.19, -4355.78, -14.71, 0); break;
        case 101120:TP(player, 1, 1454.71, -4179.42, 61.56, 0); break;

        case 1012://专业技能训练师
            if (!player->GetTeamId())
            {
                AddGossipItemFor(player, 9, "武器训练师", GOSSIP_SENDER_MAIN, 101201);
                AddGossipItemFor(player, 9, "飞行训练师", GOSSIP_SENDER_MAIN, 101202);
            }
            else
            {
                AddGossipItemFor(player, 9, "骑术训练师", GOSSIP_SENDER_MAIN, 101204);
                AddGossipItemFor(player, 9, "飞行训练师", GOSSIP_SENDER_MAIN, 101205);
            }
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 101201:TP(player, 0, -8793.120117, 613.002991, 96.8564, 0); break;
        case 101202:TP(player, 530, -676.925598, 2730.669434, 93.9085, 0); break;
        case 101204:TP(player, 530, 9268.768555, -7508.026367, 38.09, 0); break;
        case 101205:TP(player, 530, 48.719337, 2741.37085, 85.25518, 0); break;
        case 4:
            if (player->getClass() == 1) {
                if (!player->HasSpell(2458))
                    player->learnSpell(2458);

                if (!player->HasSpell(71))
                    player->learnSpell(71);

                if (!player->HasSpell(7386))
                    player->learnSpell(7386);

                if (!player->HasSpell(355))
                    player->learnSpell(355);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会战士所有任务技能");
                break;
            }
            if (player->getClass() == 3) {
                if (!player->HasSpell(982))
                    player->learnSpell(982);

                if (!player->HasSpell(2641))
                    player->learnSpell(2641);

                if (!player->HasSpell(6991))
                    player->learnSpell(6991);

                if (!player->HasSpell(1515))
                    player->learnSpell(1515);

                if (!player->HasSpell(1462))
                    player->learnSpell(1462);

                if (!player->HasSpell(883))
                    player->learnSpell(883);

                if (!player->HasSpell(136))
                    player->learnSpell(136);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会猎人所有任务技能");
                break;
            }
            if (player->getClass() == 2) {
                if (!player->HasSpell(7328))
                    player->learnSpell(7328);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会骑士所有任务技能");
                break;
            }
            if (player->getClass() == 9) {
                if (!player->HasSpell(1122))
                    player->learnSpell(1122);
                if (!player->HasSpell(691))
                    player->learnSpell(691);

                if (!player->HasSpell(712))
                    player->learnSpell(712);

                if (!player->HasSpell(688))
                    player->learnSpell(688);

                if (!player->HasSpell(697))
                    player->learnSpell(697);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会术士所有任务技能");
                break;
            }
            if (player->getClass() == 11) {
                if (!player->HasSpell(1066))
                    player->learnSpell(1066);

                if (!player->HasSpell(5487))
                    player->learnSpell(5487);

                if (!player->HasSpell(783))
                    player->learnSpell(783);

                if (!player->HasSpell(6807))
                    player->learnSpell(6807);

                if (!player->HasSpell(6795))
                    player->learnSpell(6795);

                if (!player->HasSpell(5211))
                    player->learnSpell(5211);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会德鲁伊所有任务技能");
                break;
            }
            if (player->getClass() == 7) {
                if (!player->HasSpell(8071))
                    player->learnSpell(8071);

                if (!player->HasSpell(3599))
                    player->learnSpell(3599);

                if (!player->HasSpell(5394))
                    player->learnSpell(5394);

                if (!player->HasSpell(8177))
                    player->learnSpell(8177);

                ChatHandler(player->GetSession()).SendSysMessage("你已学会萨满所有任务技能");
                break;
            }
            ChatHandler(player->GetSession()).SendSysMessage("你已学会所有任务技能");
            break;

        case 6001:
            if (player->IsInCombat())
            {
                ChatHandler(player->GetSession()).SendSysMessage("你不能在战斗中使用它!");//你不能在战斗中使用它
                break;
            }
            if (useIntegral(player, 200)) {
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                ChatHandler(player->GetSession()).SendSysMessage("你需要重新登录，然后修改阵营才会生效!");
            }
            //你需要重新登录，然后修改阵营才会生效
            //player->DestroyItemCount(item_id, 1, true, false); //消耗该物品

            break;
        case 6002:
            if (player->getLevel() < 80) {
                if (useIntegral(player, 20))
                    player->GiveXP(24100000, player);
            }
            else {
                ChatHandler(player->GetSession()).SendSysMessage("你的等级已满。");
            }

            break;
        case 6003:
            AddGossipItemFor(player, 3, "|cFF006400初级采矿|r", GOSSIP_SENDER_MAIN, 600301);
            AddGossipItemFor(player, 3, "|cFF0000FF初级采药|r", GOSSIP_SENDER_MAIN, 600302);
            AddGossipItemFor(player, 3, "|cFF0000FF初级剥皮|r", GOSSIP_SENDER_MAIN, 600303);
            AddGossipItemFor(player, 3, "|cFF006400初级附魔|r", GOSSIP_SENDER_MAIN, 600304);
            AddGossipItemFor(player, 3, "|cFF0000FF初级炼金|r", GOSSIP_SENDER_MAIN, 600305);
            AddGossipItemFor(player, 3, "|cFF006400初级铭文|r", GOSSIP_SENDER_MAIN, 600306);
            AddGossipItemFor(player, 3, "|cFF0000FF初级锻造|r", GOSSIP_SENDER_MAIN, 600307);
            AddGossipItemFor(player, 3, "|cFF006400初级珠宝|r", GOSSIP_SENDER_MAIN, 600308);
            AddGossipItemFor(player, 3, "|cFF0000FF初级工程|r", GOSSIP_SENDER_MAIN, 600309);
            AddGossipItemFor(player, 3, "|cFF006400初级裁缝|r", GOSSIP_SENDER_MAIN, 600310);
            AddGossipItemFor(player, 3, "|cFF0000FF初级制皮|r", GOSSIP_SENDER_MAIN, 600311);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 600301:
            if (!LearnProSpell(player, 30, 2575, "采矿"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600302:
            if (!LearnProSpell(player, 30, 2366, "采药"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600303:
            if (!LearnProSpell(player, 30, 8613, "剥皮"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600304:
            if (!LearnProSpell(player, 30, 7411, "附魔"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600305:
            if (!LearnProSpell(player, 30, 2259, "炼金"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600306:
            if (!LearnProSpell(player, 30, 45357, "铭文"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600307:
            if (!LearnProSpell(player, 30, 2018, "锻造"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600308:
            if (!LearnProSpell(player, 30, 25229, "珠宝"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600309:
            if (!LearnProSpell(player, 30, 4036, "工程"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600310:
            if (!LearnProSpell(player, 30, 3908, "裁缝"))
                addLowSpecialtyMenu(player, item);
            break;
        case 600311:
            if (!LearnProSpell(player, 30, 2108, "制皮"))
                addLowSpecialtyMenu(player, item);
            break;
        case 6004:
            AddGossipItemFor(player, 3, "|cFF006400升级采矿|r", GOSSIP_SENDER_MAIN, 600402);
            AddGossipItemFor(player, 3, "|cFF0000FF升级采药|r", GOSSIP_SENDER_MAIN, 600403);
            AddGossipItemFor(player, 3, "|cFF0000FF升级剥皮|r", GOSSIP_SENDER_MAIN, 600404);
            AddGossipItemFor(player, 3, "|cFF006400升级附魔|r", GOSSIP_SENDER_MAIN, 600405);
            AddGossipItemFor(player, 3, "|cFF0000FF升级炼金|r", GOSSIP_SENDER_MAIN, 600406);
            AddGossipItemFor(player, 3, "|cFF006400升级铭文|r", GOSSIP_SENDER_MAIN, 600407);
            AddGossipItemFor(player, 3, "|cFF0000FF升级锻造|r", GOSSIP_SENDER_MAIN, 600408);
            AddGossipItemFor(player, 3, "|cFF006400升级珠宝|r", GOSSIP_SENDER_MAIN, 600409);
            AddGossipItemFor(player, 3, "|cFF0000FF升级工程|r", GOSSIP_SENDER_MAIN, 600410);
            AddGossipItemFor(player, 3, "|cFF006400升级裁缝|r", GOSSIP_SENDER_MAIN, 600411);
            AddGossipItemFor(player, 3, "|cFF0000FF升级制皮|r", GOSSIP_SENDER_MAIN, 600412);
            AddGossipItemFor(player, 3, "|cFF0000FF升级烹饪|r", GOSSIP_SENDER_MAIN, 600413);
            AddGossipItemFor(player, 3, "|cFF0000FF升级急救|r", GOSSIP_SENDER_MAIN, 600414);
            AddGossipItemFor(player, 3, "|cFF0000FF升级钓鱼|r", GOSSIP_SENDER_MAIN, 600415);
            AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 6);
            AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
            SendGossipMenuFor(player, 1, item->GetGUID());
            break;
        case 600402:
            if (!AddProSpell(player, 30, 2575, 2576, 3564, 10248, 29354, 50310, 186, "采矿"))
                addUpgrademajormenu(player, item);
            break;

        case 600403:
            if (!AddProSpell(player, 30, 2366, 2368, 3570, 11993, 28695, 50300, 182, "采药"))
                addUpgrademajormenu(player, item);
            break;
        case 600404:
            if (!AddProSpell(player, 30, 8613, 8617, 8618, 10768, 32678, 50305, 393, "剥皮"))
                addUpgrademajormenu(player, item);
            break;
        case 600405:
            if (!AddProSpell(player, 30, 7411, 7412, 7413, 13920, 28029, 51313, 333, "附魔"))
                addUpgrademajormenu(player, item);

            break;
        case 600406:
            if (!AddProSpell(player, 30, 2259, 3101, 3464, 11611, 28596, 51304, 171, "炼金"))
                addUpgrademajormenu(player, item);
            break;

        case 600407:
            if (!AddProSpell(player, 30, 45357, 45358, 45359, 45360, 45361, 45363, 773, "铭文"))
                addUpgrademajormenu(player, item);
            break;
        case 600408:
            if (!AddProSpell(player, 30, 2018, 3100, 3538, 9785, 29844, 51300, 164, "锻造"))
                addUpgrademajormenu(player, item);
            break;
        case 600409:
            if (!AddProSpell(player, 30, 25229, 25230, 28894, 28895, 28897, 51311, 755, "珠宝"))
                addUpgrademajormenu(player, item);
            break;
        case 600410:
            if (!AddProSpell(player, 30, 4036, 4037, 4038, 12656, 30350, 51306, 202, "工程"))
                addUpgrademajormenu(player, item);
            break;
        case 600411:
            if (!AddProSpell(player, 30, 3908, 3909, 3910, 12180, 26790, 51309, 197, "裁缝"))
                addUpgrademajormenu(player, item);
            break;
        case 600412:
            if (!AddProSpell(player, 30, 2108, 3104, 3811, 10662, 32549, 51302, 165, "制皮"))
                addUpgrademajormenu(player, item);
            break;

        case 600413:
            if (!AddProSpell(player, 30, 2550, 3102, 3413, 18260, 33359, 51296, 185, "烹饪"))
                addUpgrademajormenu(player, item);
            break;

        case 600414:
            if (!AddProSpell(player, 30, 3273, 3274, 7924, 10846, 27028, 45542, 129, "急救"))
                addUpgrademajormenu(player, item);
            break;
        case 600415:
            if (!AddProSpell(player, 30, 7620, 7731, 7732, 18248, 33095, 51294, 356, "钓鱼"))
                addUpgrademajormenu(player, item);
            break;

        }
        return;
    }

    int TP(Player* player, float mapId, float x, float y, float z, float o) {
        if (player->IsInFlight())
        {
            player->GetMotionMaster()->MovementExpired();
            player->m_taxi.ClearTaxiDestinations();
        }
        player->TeleportTo(mapId, x, y, z, o);
        return 1;
    }
    bool  LearnProSpell(Player* player, uint32 integral, uint32 spellid, std::string name) {
        if (player->HasSpell(spellid)) {
            ChatHandler(player->GetSession()).SendSysMessage("你已学会学习初级" + name + "，不用再学习。");
            return false;
        }
        if (useIntegral(player, integral)) {
            player->learnSpell(spellid);
            ChatHandler(player->GetSession()).SendSysMessage("你已学会学习初级" + name + "。");
            return true;
        }
        return false;
    }
    bool  AddProSpell(Player* player, uint32 integral, uint32 spellid1, uint32 spellid2, uint32 spellid3, uint32 spellid4, uint32 spellid5, uint32 spellid6, uint32 skillid, std::string name) {
        if (!player->HasSpell(spellid1)) {
            ChatHandler(player->GetSession()).SendSysMessage("你还未学习初级" + name + "。");
            return false;
        }
        if (player->GetSkillValue(skillid) < 450) {
            if (useIntegral(player, integral)) {
                if (!player->HasSpell(spellid2)) {
                    player->learnSpell(spellid2);
                }
                   
                if (!player->HasSpell(spellid3)) {
                    player->learnSpell(spellid3);
                }
                    
                if (!player->HasSpell(spellid4)) {
                    player->learnSpell(spellid4);
                }
                    
                if (!player->HasSpell(spellid5)) {
                    player->learnSpell(spellid5);
                }
                    
                if (!player->HasSpell(spellid6)) {
                    player->learnSpell(spellid6);
                }
                player->UpdateSkill(skillid, 450);
                //player->SaveToDB(false, false);
                if (skillid == 333) {
                    player->AddItem(44452, 1);
                }
                ChatHandler(player->GetSession()).SendSysMessage("升级" + name + "技能成功");
                return true;
            }
            else
            {
                return false;
            }
            
        }
        else
        {
            ChatHandler(player->GetSession()).SendSysMessage("你的" + name + "专业已满。不用再升级。");
            return false;
        }
    }
    bool useIntegral(Player* player, uint32 integral) {
        //ChatHandler(player->GetSession()).SendSysMessage(std::to_string(player->GetItemCount(37742)));
        if (player->GetItemCount(37742) >= integral) {
            
            player->DestroyItemCount(37742, integral, true, false);
            ChatHandler(player->GetSession()).SendSysMessage("剩余" + std::to_string(player->GetItemCount(37742)) + "积分");
            return true;
        }
        else
        {
            ChatHandler(player->GetSession()).SendSysMessage("你不足" + std::to_string(integral) + "积分");
            return false;
        }
        

    }
    bool addmenu(Player* player, Item* item) {
        ClearGossipMenuFor(player);
        CloseGossipMenuFor(player);
        AddGossipItemFor(player, 2, "【炉石】", GOSSIP_SENDER_MAIN, 1);
        AddGossipItemFor(player, 9, "【地图传送】", GOSSIP_SENDER_MAIN, 2);
        AddGossipItemFor(player, 0, "【解除虚弱】", GOSSIP_SENDER_MAIN, 3, "是否解除虚弱", 20000, false);
        AddGossipItemFor(player, 3, "【学习任务技能】", GOSSIP_SENDER_MAIN, 4);
        AddGossipItemFor(player, 3, "【免费学习骑术】", GOSSIP_SENDER_MAIN, 5);
        AddGossipItemFor(player, 9, "【积分使用】", GOSSIP_SENDER_MAIN, 6);
        SendGossipMenuFor(player, 1, item->GetGUID());
        return true;
    }
    bool addUpgrademajormenu(Player* player, Item* item) {
        AddGossipItemFor(player, 3, "|cFF006400升级采矿|r", GOSSIP_SENDER_MAIN, 600402);
        AddGossipItemFor(player, 3, "|cFF0000FF升级采药|r", GOSSIP_SENDER_MAIN, 600403);
        AddGossipItemFor(player, 3, "|cFF0000FF升级剥皮|r", GOSSIP_SENDER_MAIN, 600404);
        AddGossipItemFor(player, 3, "|cFF006400升级附魔|r", GOSSIP_SENDER_MAIN, 600405);
        AddGossipItemFor(player, 3, "|cFF0000FF升级炼金|r", GOSSIP_SENDER_MAIN, 600406);
        AddGossipItemFor(player, 3, "|cFF006400升级铭文|r", GOSSIP_SENDER_MAIN, 600407);
        AddGossipItemFor(player, 3, "|cFF0000FF升级锻造|r", GOSSIP_SENDER_MAIN, 600408);
        AddGossipItemFor(player, 3, "|cFF006400升级珠宝|r", GOSSIP_SENDER_MAIN, 600409);
        AddGossipItemFor(player, 3, "|cFF0000FF升级工程|r", GOSSIP_SENDER_MAIN, 600410);
        AddGossipItemFor(player, 3, "|cFF006400升级裁缝|r", GOSSIP_SENDER_MAIN, 600411);
        AddGossipItemFor(player, 3, "|cFF0000FF升级制皮|r", GOSSIP_SENDER_MAIN, 600412);
        AddGossipItemFor(player, 3, "|cFF0000FF升级烹饪|r", GOSSIP_SENDER_MAIN, 600413);
        AddGossipItemFor(player, 3, "|cFF0000FF升级急救|r", GOSSIP_SENDER_MAIN, 600414);
        AddGossipItemFor(player, 3, "|cFF0000FF升级钓鱼|r", GOSSIP_SENDER_MAIN, 600415);
        AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 6);
        AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
        SendGossipMenuFor(player, 1, item->GetGUID());
        return true;
    }
    bool addLowSpecialtyMenu(Player* player, Item* item) {
        AddGossipItemFor(player, 3, "|cFF006400初级采矿|r", GOSSIP_SENDER_MAIN, 600301);
        AddGossipItemFor(player, 3, "|cFF0000FF初级采药|r", GOSSIP_SENDER_MAIN, 600302);
        AddGossipItemFor(player, 3, "|cFF0000FF初级剥皮|r", GOSSIP_SENDER_MAIN, 600303);
        AddGossipItemFor(player, 3, "|cFF006400初级附魔|r", GOSSIP_SENDER_MAIN, 600304);
        AddGossipItemFor(player, 3, "|cFF0000FF初级炼金|r", GOSSIP_SENDER_MAIN, 600305);
        AddGossipItemFor(player, 3, "|cFF006400初级铭文|r", GOSSIP_SENDER_MAIN, 600306);
        AddGossipItemFor(player, 3, "|cFF0000FF初级锻造|r", GOSSIP_SENDER_MAIN, 600307);
        AddGossipItemFor(player, 3, "|cFF006400初级珠宝|r", GOSSIP_SENDER_MAIN, 600308);
        AddGossipItemFor(player, 3, "|cFF0000FF初级工程|r", GOSSIP_SENDER_MAIN, 600309);
        AddGossipItemFor(player, 3, "|cFF006400初级裁缝|r", GOSSIP_SENDER_MAIN, 600310);
        AddGossipItemFor(player, 3, "|cFF0000FF初级制皮|r", GOSSIP_SENDER_MAIN, 600311);
        AddGossipItemFor(player, 0, "上一页", GOSSIP_SENDER_MAIN, 6);
        AddGossipItemFor(player, 0, "主菜单", GOSSIP_SENDER_MAIN, 10);
        SendGossipMenuFor(player, 1, item->GetGUID());
        return true;
    }
};

void AddSC_Obj_Services()
{
    new Obj_Services();
}
