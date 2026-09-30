# 03 — CONVENTIONS

## 1. Naming asset
| Asset | Prefix | Ví dụ |
|---|---|---|
| Blueprint | `BP_` | `BP_RestPoint` |
| Character Blueprint | `BP_CH_` | `BP_CH_Player`, `BP_CH_Hollow_Sword` |
| Static Mesh | `SM_` | `SM_Castle_Wall_A` |
| Skeletal Mesh | `SK_` | `SK_CH_Knight` |
| Skeleton | `SKEL_` | `SKEL_Mannequin` |
| Physics Asset | `PHYS_` | `PHYS_CH_Knight` |
| Material / Instance / Function | `M_` / `MI_` / `MF_` | `M_Master_Surface`, `MI_Stone_Wet` |
| Texture | `T_` + hậu tố | `T_Knight_BC`, `_N`, `_ORM`, `_E` (emissive), `_M` (mask) |
| Animation Sequence | `A_` | `A_GS_Light01` |
| Montage | `AM_` | `AM_GS_Light01` |
| Anim Blueprint | `ABP_` | `ABP_Player` |
| Blend Space | `BS_` | |
| Anim Notify / NotifyState (BP) | `AN_` / `ANS_` | `ANS_WeaponTrace` |
| Pose Search Database / Schema | `PSD_` / `PSS_` | |
| Chooser Table | `CHT_` | |
| IK Rig / Retargeter | `IK_` / `RTG_` | |
| Niagara System / Emitter | `NS_` / `NE_` | `NS_Hit_Blood` |
| Sound Wave | `SW_` | |
| Sound Cue | `SC_` | |
| MetaSound Source / Patch | `MSS_` / `MSP_` | `MSS_Footstep` |
| Physical Material | `PM_` | `PM_Stone` |
| Data Asset | `DA_` | `DA_Weapon_GreatSword_Iron` |
| Data Table / Curve Table | `DT_` / `CT_` | `DT_LevelUpCost` |
| Gameplay Ability / Effect / Cue | `GA_` / `GE_` / `GC_` | `GA_Attack_Light`, `GE_Damage_Physical`, `GC_Hit_Flesh` |
| Input Action / Mapping Context | `IA_` / `IMC_` | `IA_Dodge`, `IMC_Gameplay` |
| StateTree | `ST_` | `ST_Enemy_Melee` |
| EQS Query | `EQS_` | |
| Widget Blueprint | `WBP_` | `WBP_HUD` |
| Level | `L_` | `L_Dungeon01`, `L_Test_Combat` |
| Level Sequence | `LS_` | |

Quy tắc: `Prefix_Nhóm_Tên_Biến thể_Số` — PascalCase, không dấu cách, không tiếng Việt có dấu, số 2 chữ số (`01`).

## 2. Thư mục Content
```
Content/
├── Eclipse/
│   ├── Core/                 # GameMode BP, GameInstance BP, default settings
│   ├── Characters/{Player, Shared}/
│   ├── Enemies/{Hollow, ...}/
│   ├── Bosses/{Warden, ...}/
│   ├── Combat/{Abilities, Effects, Cues, Attacks}/
│   ├── Weapons/{Sword, GreatSword, Spear, Shield}/
│   ├── Items/
│   ├── Animation/{Player, Enemies, Bosses, Shared}/
│   ├── AI/{StateTrees, EQS}/
│   ├── Input/{Actions, Contexts}/
│   ├── World/{Maps, Architecture, Props, Foliage}/
│   ├── Materials/{Master, Functions, Shared}/
│   ├── VFX/{Combat, Environment, Boss}/
│   ├── Audio/{Music, SFX, MetaSounds}/
│   └── UI/{HUD, Menus, Icons, Fonts}/
├── Developers/               # sandbox cá nhân, không được reference từ Eclipse/
└── (GASP, pack Fab)          # giữ nguyên đường dẫn gốc của pack, không trộn vào Eclipse/
```
Asset mua/tải về: **để nguyên thư mục gốc**. Chỉ copy/migrate cái thực sự dùng vào `Eclipse/` khi đã chốt.

## 3. C++
- Class: `AEclipse*`, `UEclipse*`, `FEclipse*`, `IEclipse*`, `EEclipse*` (enum).
- File name = class name bỏ tiền tố: `EclipseCombatComponent.h`.
- `TObjectPtr<>` cho UPROPERTY pointer. Mọi UObject member **phải** có `UPROPERTY()`.
- Giá trị gameplay tunable: `UPROPERTY(EditDefaultsOnly, Category="Eclipse|...")` hoặc Data Asset — không hardcode.
- Log category: `DECLARE_LOG_CATEGORY_EXTERN(LogEclipse, Log, All)`; thêm `LogEclipseCombat`, `LogEclipseAI` khi cần.
- Không Tick trừ khi cần; ưu tiên timer/delegate/AnimNotify.
- Comment tiếng Anh, ngắn, giải thích **tại sao**.
- Include theo quy tắc tầng `01_ARCHITECTURE.md` §3.

## 4. Scale & đơn vị
- 1 UU = 1 cm. Nhân vật ~180 cm. Kiếm 100–140 cm. Cửa 220–300 cm. Hành lang tối thiểu 300 cm rộng (camera + lock-on cần chỗ).
- Blender: Unit Scale = 0.01, Length = Centimeters **hoặc** Unit Scale 1.0 + export scale đúng — chọn một, ghi trong `06_ART_PIPELINE.md`, không đổi.
- Asset trong Unreal luôn Scale = (1,1,1).

## 5. Git
- Branch: `main`, `task/T-XXX-ten`.
- Commit: `T-XXX: mô tả`. Commit không có task: `chore: ...` / `docs: ...`.
- `.uasset`/`.umap` qua Git LFS, **lockable**.
