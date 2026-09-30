# BACKLOG

Tier: **A** = Claude, **B** = GPT Luna / Gemini Flash, **I** = GPT Sol, **H** = Bạn.
Task có card chi tiết được link. Task khác sẽ được Tier A viết card khi tới milestone.

## M0 — Setup
| ID | Task | Tier | Phụ thuộc | Status |
|---|---|---|---|---|
| [T-001](T-001-toolchain.md) | Cài workload VS "Game development with C++", xác minh MSVC/SDK hợp với UE 5.8 | H (+A hỗ trợ) | — | TODO |
| [T-002](T-002-git-setup.md) | `git init`, `.gitignore`, `.gitattributes` (LFS + lockable), quyết định remote/backup | B | — | TODO |
| [T-003](T-003-create-project.md) | Tạo project C++ `Eclipse` trong `Unreal/`, module, targets, plugin M0 | A + H | T-001 | TODO |
| T-004 | Cấu hình DDC/Zen giới hạn dung lượng, editor scalability High, ghi kết quả vào `05_HARDWARE_AND_DISK.md` | A viết hướng dẫn → H làm | T-003 | TODO |
| [T-005](T-005-gasp-research.md) | Tìm hiểu GASP bản tương thích 5.8: dung lượng, cách migrate, asset cần giữ | B (Gemini) | — | TODO |
| T-006 | `docs/THIRD_PARTY.md` mẫu + `Tools/check_disk.sh` in dung lượng các thư mục lớn | B | T-002 | TODO |
| T-007 | Mood board + tone art direction (4–6 ảnh) cho khu dungeon đầu tiên | I | — | TODO |

## M1 — Player feel
| ID | Task | Tier | Phụ thuộc |
|---|---|---|---|
| T-010 | `Core/`: log category, `EclipseGameplayTags` (native tags §2 spec), 4 interface, `UEclipseEventSubsystem` | A | T-003 |
| T-011 | `Abilities/`: `UEclipseAbilitySystemComponent`, `UEclipseCombatAttributeSet`, `UEclipseGameplayAbility` base | A | T-010 |
| T-012 | `AEclipseCharacterBase`, `AEclipsePlayerCharacter`, `AEclipsePlayerController`, GameMode — header | A | T-011 |
| T-013 | Thân hàm `.cpp` cho các class T-012 theo comment header | B (GPT Luna) | T-012 |
| T-014 | Script Python Editor tạo `IA_*` + `IMC_Gameplay` theo danh sách trong spec | B | T-003 |
| T-015 | Migrate GASP locomotion vào project + hook vào `BP_CH_Player` | H (A viết hướng dẫn) | T-005, T-013 |
| T-016 | Stamina regen (GE periodic + delay tag) + Sprint ability | A | T-011 |
| T-017 | `UEclipseLockOnComponent` header + thuật toán score | A | T-012 |
| T-018 | `UEclipseLockOnComponent.cpp` phần FindTargets/LOS/clear (theo header) | B | T-017 |
| T-019 | Camera Soulslike (spring arm, lag, lock-on framing) | A | T-017 |
| T-020 | Greybox `L_Test_Movement` (dốc, bậc, hành lang, cột) | H | T-015 |
| T-021 | Audit include-tầng + naming toàn repo cuối M1 (chỉ báo cáo) | B (Gemini) | cuối M1 |

## M2 → M9
Tier A tách task khi bắt đầu từng milestone (xem `00_MASTER_PLAN.md`).

## Ý tưởng để sau (không làm trước Vertical Slice)
- Open world / World Partition / Data Layers / HLOD
- PCG, Mass AI, SmartObjects
- Magic, ranged, NPC, quest, horse (`IMC_Horse`)
- Multiplayer / co-op
