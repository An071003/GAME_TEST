# BACKLOG

Tier: **A** = Claude (Opus 5.5; Sonnet dự phòng) / GPT 6.1, **B** = GPT Luna / Gemini Flash, **I** = GPT Sol, **H** = Bạn.
Task có card chi tiết được link. Task khác sẽ được Tier A viết card khi tới lượt (xem "Thứ tự làm").

## M0 — Setup
| ID | Task | Tier | Phụ thuộc | Status |
|---|---|---|---|---|
| [T-001](T-001-toolchain.md) | Cài workload VS "Game development with C++", xác minh MSVC/SDK hợp với UE 5.8 | H (+A hỗ trợ) | — | DONE khi merge T-003 (build PASS) |
| [T-002](T-002-git-setup.md) | `git init`, `.gitignore`, `.gitattributes` (LFS + lockable), remote | B | — | DONE (đang dùng; remote GitHub) |
| [T-003](T-003-create-project.md) | Tạo project C++ `Eclipse` trong `Unreal/`, module, targets, plugin M0 | A + H | T-001 | REVIEW → chờ merge |
| [T-004](T-004-ddc-scalability.md) | Giới hạn Zen/DDC cache, editor scalability High, ghi số liệu vào `05_HARDWARE_AND_DISK.md` | A → H | T-003 | TODO |
| [T-005](T-005-gasp-research.md) | Nghiên cứu GASP 5.8 | B (Gemini) | — | APPROVED (kèm đính chính) → chờ merge |
| [T-006](T-006-third-party-disk-script.md) | `docs/THIRD_PARTY.md` + `Tools/check_disk.sh` | B (Gemini) | T-002 | TODO |
| T-007 | Mood board + tone art direction (4–6 ảnh) cho khu dungeon đầu tiên | I | — | TODO |
| [T-008](T-008-gasp-inspect.md) | Tạo project GASP tạm, kiểm chứng plugin/skeleton/trajectory/dung lượng → đề xuất ADR-006 | H + A | T-005 | REVIEW (chờ chủ dự án chọn skeleton) |

**M0 xong khi:** T-003, T-005 merge; T-004 xong; T-008 có quyết định skeleton. (T-006, T-007 không chặn M1.)

## M1 — Player feel
| ID | Task | Tier | Phụ thuộc | Status |
|---|---|---|---|---|
| [T-010](T-010-core.md) | `Core/`: `EclipseGameplayTags`, 4 interface, `EclipseTypes`, `UEclipseEventSubsystem` + test | A | T-003 | TODO |
| [T-011](T-011-abilities-base.md) | `Abilities/`: ASC, `UEclipseCombatAttributeSet`, `UEclipseGameplayAbility` base + test | A | T-010 | TODO |
| [T-012](T-012-character-headers.md) | Header + `.cpp` khung: CharacterBase, PlayerCharacter, PlayerController, GameMode, GameInstance, InputConfig; viết card T-013 | A | T-011 | TODO |
| T-013 | Thân hàm `.cpp` cho các class T-012 theo comment `// T-013:` | B (GPT Luna) | T-012 | card viết trong T-012 |
| [T-014](T-014-input-assets-script.md) | Script Python tạo 11 `IA_*` + `IMC_Gameplay` (bước 0: Lead bật PythonScriptPlugin) | A → B (GPT Luna) → H | T-003 | TODO |
| T-015 | Migrate GASP locomotion vào project + hook vào `BP_CH_Player`; đo CPU Motion Matching bằng Insights | H (A viết hướng dẫn) | T-008, T-013 | TODO |
| T-016 | Stamina regen (GE periodic + delay tag) + Sprint ability | A | T-011 | TODO |
| T-017 | `UEclipseLockOnComponent` header + thuật toán score | A | T-012 | TODO |
| T-018 | `UEclipseLockOnComponent.cpp` phần FindTargets/LOS/clear (theo header) | B | T-017 | card viết trong T-017 |
| T-019 | Camera Soulslike (spring arm, lag, lock-on framing) | A | T-017 | TODO |
| T-020 | Greybox `L_Test_Movement` (dốc, bậc, hành lang ≥ 300 cm, cột che) + đặt làm `GameDefaultMap` | H | T-003 | TODO |
| T-021 | Audit include-tầng + naming toàn repo cuối M1 (chỉ báo cáo) | B (Gemini) | cuối M1 | TODO |

**M1 xong khi** (master plan): chạy, sprint tốn stamina, lock-on, strafe quanh target trông tự nhiên — con người playtest trên `L_Test_Movement`.

## Thứ tự làm (kế hoạch 2026-10-01)
Mỗi đợt: các dòng cùng đợt chạy song song được (khác người/khác file).

| Đợt | Claude (A) | Tier B | Bạn (H) | Tier I |
|---|---|---|---|---|
| **1** | Merge-ready T-003/T-005 → làm T-004 (ini + hướng dẫn) → T-010 → bước 0 của T-014 | T-006 (Gemini) | Merge T-003, T-005; tải GASP cho T-008; làm phần Human của T-004 | T-007 |
| **2** | Phần Claude của T-008 (đọc GASP58, đề xuất skeleton) → T-011 → T-012 | T-014 (Luna) | Chọn phương án skeleton; chạy script T-014; bắt đầu greybox T-020 | — |
| **3** | T-016, T-017, review T-013 | T-013 (Luna) | Tiếp T-020 | — |
| **4** | T-019, viết hướng dẫn T-015, review T-018 | T-018 | T-015 (migrate GASP, hook player) | — |
| **5** | Sửa lỗi playtest | T-021 audit (Gemini) | Playtest tiêu chí M1 | — |

Ghi chú:
- T-020 không cần chờ T-015: greybox dùng Mannequin mặc định cũng được (đã nới phụ thuộc).
- Từ T-003 còn treo: `Substrate=True` (mặc định template) — Claude đánh giá ở T-004 với 6 GB VRAM; `GameDefaultMap=OpenWorld` → đổi trong T-020.

## M2 → M9
Tier A tách task khi bắt đầu từng milestone (xem `00_MASTER_PLAN.md`).

## Ý tưởng để sau (không làm trước Vertical Slice)
- Open world / World Partition / Data Layers / HLOD
- PCG, Mass AI, SmartObjects
- Magic, ranged, NPC, quest, horse (`IMC_Horse`)
- Multiplayer / co-op
