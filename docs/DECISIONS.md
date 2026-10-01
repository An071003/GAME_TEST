# DECISIONS — Nhật ký quyết định kiến trúc (ADR)

> **Mọi AI agent phải đọc file này.** Các quyết định ở đây là CHỐT. Không agent nào được tự ý đảo ngược.
> Muốn thay đổi → viết đề xuất vào mục "Đề xuất chờ duyệt" ở cuối file, chủ dự án + Tier A duyệt.

Nguồn gốc: kế hoạch ban đầu (do ChatGPT soạn, 54 mục) được review ngày 2026-09-30. Phần lớn giữ nguyên.
Các ADR dưới đây là những chỗ **sửa lại** so với kế hoạch gốc, kèm lý do.

---

## ADR-001 — Một module C++ runtime duy nhất `Eclipse` (không phải 8 module)
- **Gốc:** 8 module (`EclipseCore`, `EclipseGameplay`, `EclipseCombat`, ...).
- **Chốt:** 1 module runtime `Eclipse`, chia thư mục con theo hệ thống (`Core/`, `Abilities/`, `Combat/`, ...). Thêm module `EclipseEditor` khi thật sự cần code editor-only.
- **Lý do:** Dự án solo + agent yếu. Nhiều module = nhiều `Build.cs`, `*_API` macro, lỗi linker, circular dependency — đúng loại lỗi mà model yếu hay gây ra và khó tự sửa. Quy tắc phụ thuộc (Combat không gọi UI...) vẫn được giữ bằng **quy tắc include** trong `01_ARCHITECTURE.md` và được review. Có thể tách module sau khi code ổn định (việc tách là cơ học).

## ADR-002 — GAS xây CÙNG LÚC với combat (không tách Phase 4 / Phase 5)
- **Gốc:** Phase 04 Combat → Phase 05 GAS.
- **Chốt:** GAS được dựng ở M1 (setup) và combat được viết trực tiếp bằng Gameplay Ability ở M2.
- **Lý do:** Kế hoạch gốc tự nói "GAS là xương sống của combat". Làm combat trước rồi mới chuyển sang GAS = viết combat 2 lần.

## ADR-003 — Bỏ các component trùng chức năng với GAS
- **Bỏ:** `UAttributeComponent` (đã có AttributeSet), `UStatusComponent` (status = GameplayEffect + Tag), `UHitReactionComponent` (hit reaction = Gameplay Ability `GA_HitReact`).
- **Chuyển:** `ULockOnTargetComponent` chỉ có ở **Player**. Enemy/Boss chỉ cần `IEclipseTargetable` + socket/điểm target.
- **Lý do:** Hai nguồn sự thật cho cùng một dữ liệu (Health trong component VÀ trong AttributeSet) là nguồn bug số 1 trong dự án GAS.

## ADR-004 — Vũ khí: một class `AEclipseMeleeWeapon` + Data Asset, KHÔNG subclass theo loại
- **Gốc:** `AMeleeWeapon` → `Sword`, `Katana`, `GreatSword`, `Spear`, `Hammer`.
- **Chốt:** Loại vũ khí là `FGameplayTag` (`Weapon.Type.GreatSword`) trong `UEclipseWeaponDefinition`. Chỉ tạo subclass khi hành vi thật sự khác (ví dụ ranged cần projectile).

## ADR-005 — Single-player. Không thiết kế cho multiplayer.
- ASC đặt trên Character (kể cả Player), không đặt trên PlayerState.
- Không viết code replication, không dùng prediction key thủ công.
- **Lý do:** Networking nhân đôi độ phức tạp GAS. Nếu sau này cần co-op thì đó là dự án refactor riêng.

## ADR-006 — Skeleton: dùng skeleton UE5 Mannequin (Manny/Quinn) làm skeleton chuẩn của người chơi và enemy dạng người
- **Gốc:** tự tạo `SK_Player_Skeleton`.
- **Chốt:** dùng hệ xương tương thích UE5 Mannequin. Nhân vật tự làm trong Blender phải skin vào hệ xương này (tên bone + hierarchy giống hệt).
- **Lý do:** Solo dev không thể tự animate đủ dữ liệu cho Motion Matching. Dùng skeleton Mannequin → dùng được Game Animation Sample (locomotion Motion Matching miễn phí của Epic), animation pack trên Fab, IK Retargeter không đau đầu.

## ADR-007 — Locomotion khởi đầu từ Game Animation Sample (GASP) của Epic
- Motion Matching lấy dataset từ GASP (miễn phí). Combat animation: pack trên Fab / retarget / tự key trong Blender.
- Phải kiểm tra bản GASP tương thích UE 5.8 (task T-005).

## ADR-008 — Thứ tự phase mới, có "Fun Gate" trước khi làm art
Xem `00_MASTER_PLAN.md`. Thay đổi chính:
- Thêm **vòng lặp Soulslike cốt lõi** (rest point, chết → rơi tiền → nhặt lại, bình máu, respawn enemy) — kế hoạch gốc thiếu hoàn toàn.
- Thêm **Input buffer / cancel window / hitstop** vào combat — kế hoạch gốc thiếu, đây là thứ quyết định "cảm giác" Soulslike.
- **Open World không phải Phase 15 mặc định.** Nó là mục "có thể" sau Vertical Slice, và chỉ khi phần cứng cho phép. Mặc định: các khu vực liên kết (Dark Souls 1 style), mỗi khu một level.

## ADR-009 — Hardware thật quyết định scope (RTX 4050 6GB VRAM, ổ 512GB còn ~113GB, không có ổ phụ)
- Kế hoạch gốc mục 49 giả định có ổ phụ — **không có**. Xem `05_HARDWARE_AND_DISK.md`.
- Texture tối đa 2K cho hầu hết asset, 4K chỉ cho hero/boss. **Không 8K.**
- Không bật MassEntity / MassGameplay / SmartObjects / PCG ở giai đoạn đầu.
- ArtSource (.blend, .psd, texture gốc) **không** đưa vào Git LFS trên ổ C (LFS lưu 2 bản → tốn gấp đôi). Để ngoài repo, backup lên cloud/ổ ngoài.

## ADR-010 — Gameplay Tag: tag mà C++ dùng → khai báo native trong C++; tag chỉ content dùng → `DefaultGameplayTags.ini`
- File native: `Source/Eclipse/Core/EclipseGameplayTags.h/.cpp` (Tier A sở hữu).
- Không bao giờ dùng `FGameplayTag::RequestGameplayTag(TEXT("..."))` bằng string rải rác trong code.

## ADR-011 — Event bus: `UEclipseEventSubsystem` (GameInstanceSubsystem)
- Broadcast theo `FGameplayTag` channel + payload `FInstancedStruct`.
- UI đọc attribute qua delegate của ASC (`GetGameplayAttributeValueChangeDelegate`), không poll mỗi tick.
- Không dùng Lyra GameplayMessageRouter (plugin của Lyra, không phải engine) để tránh phụ thuộc copy code ngoài.

## ADR-012 — Tag blocking cho combo
- **Gốc:** `Ability.Attack.Heavy` bị block bởi `State.Attacking` → như vậy không thể chain light→heavy.
- **Chốt:** Khi đang tấn công, input mới đi vào **input buffer**; chỉ được kích hoạt khi tag `Window.Combo` hoặc `Window.Cancel` đang có (do AnimNotifyState thêm vào). Chi tiết ở `04_COMBAT_GAS_SPEC.md`.

## ADR-013 — Weapon trace dùng sweep giữa vị trí socket frame trước và frame hiện tại
- Không overlap collision đơn thuần (bỏ lỡ hit khi FPS thấp hoặc vũ khí vung nhanh).
- Mỗi lần vung có danh sách actor đã trúng để không hit 2 lần.

---

## Đề xuất chờ duyệt
### Đề xuất #1 — Cách xử lý skeleton khi dùng GASP (chạm ADR-006) — *chờ chủ dự án chọn* (Claude, 2026-10-01)
**Dữ kiện đã xác minh (T-008, `docs/research/GASP_UE58.md` §9):** GASP chạy trên `UEFN_Mannequin`, khác UE5 Mannequin (thiếu xương corrective/twist, có `props_root`/`contact_*`...). Epic ship sẵn `RTG_UEFN_to_UE5_Mannequin` và `ABP_GenericRetarget` (retarget **lúc chạy**). Project GASP có sẵn cả `SK_Mannequin`/Manny/Quinn.

| Phương án | Ưu | Nhược |
|---|---|---|
| **A.** Player dùng thẳng `SK_UEFN_Mannequin` làm skeleton chuẩn (sửa ADR-006) | Không retarget, rẻ CPU, dùng GASP nguyên bản | Anim pack Fab (nhắm UE4/UE5 Mannequin) phải retarget **offline** sang UEFN; nhân vật Blender phải skin theo skeleton ít xương hơn; lệch tài liệu hiện tại |
| **B.** Giữ ADR-006 (UE5 Mannequin cho mesh/art/anim combat), locomotion GASP **retarget runtime** qua `ABP_GenericRetarget` cho **player** | Làm được ngay, giữ pipeline art/Fab; enemy dùng ABP thường không Motion Matching | Tốn CPU thêm cho retarget (chưa đo); chưa rõ montage combat chạy ở skeleton nào (*CHƯA XÁC MINH*) |
| **C.** Retarget **offline** toàn bộ animation GASP cần dùng sang UE5 Mannequin, dựng lại PSD/PSS/Chooser | Runtime sạch, đúng ADR-006 | Nhiều giờ thao tác Editor, nhân đôi ~1.6 GB animation, dễ hỏng schema |

**Khuyến nghị của Lead:** **B làm thử trước** (spike ở T-015: 1 player, đo Insights, thử chạy 1 montage tấn công). Tiêu chí chuyển phương án: Game thread của player > 3 ms ở Scalability High ngoài Editor → chuyển sang A (nếu art/Fab chấp nhận được) hoặc C. **Chưa đổi ADR-006 cho tới khi spike có số đo.**
