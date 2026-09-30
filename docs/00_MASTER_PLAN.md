# 00 — MASTER PLAN

## Mục tiêu thật sự
Không phải "làm game AAA". Mục tiêu đo được:

> **Vertical Slice 20–30 phút**: 1 nhân vật, 2–3 vũ khí, 3–4 loại enemy, 1 boss 2 phase, 1 khu dungeon liên kết có shortcut,
> vòng lặp Soulslike đầy đủ (rest → khám phá → chết → nhặt lại tiền), chạy ổn định **60 FPS trên chính laptop RTX 4050 ở preset High**.

Mọi thứ không phục vụ Vertical Slice → ghi vào backlog, không làm.

## Nguyên tắc
1. **Greybox trước, art sau.** Không sculpt/texture bất cứ thứ gì trước khi qua Fun Gate (M6).
2. **Mỗi milestone kết thúc bằng một build chơi được.** Không có "milestone chỉ toàn code nền".
3. **Cảm giác combat > số lượng tính năng.** 1 vũ khí có cảm giác tốt hơn 10 vũ khí dở.

---

## Milestones

Ước lượng thời gian giả định 1 người + AI, ~20h/tuần. Chỉ mang tính tham khảo.

### M0 — Setup (≈1 tuần)
- Toolchain: VS 2026 + workload "Game development with C++", xác minh MSVC tương thích UE 5.8.
- Git + Git LFS, `.gitignore`, `.gitattributes`, repo khởi tạo.
- Tạo project C++ `Eclipse`, module `Eclipse`, bật plugin tối thiểu.
- Cấu hình DDC, scalability editor cho máy 6GB VRAM.
- **Xong khi:** mở project, build C++ PASS, commit đầu tiên có trên remote/backup.

### M1 — Player feel (≈3 tuần)
- Import GASP (Game Animation Sample) locomotion Motion Matching vào project.
- `AEclipseCharacterBase`, `AEclipsePlayerCharacter`, `AEclipsePlayerController`, Enhanced Input.
- GAS setup: ASC trên character, `UEclipseCombatAttributeSet` (Health/Stamina/Poise), stamina regen.
- Camera Soulslike (spring arm, lag, collision) + Lock-on (score target, switch trái/phải).
- Greybox test map: dốc, bậc thang, hẹp, rộng, cột che khuất lock-on.
- **Xong khi:** chạy, sprint (tốn stamina), lock-on, strafe quanh target trông tự nhiên.

### M2 — Combat core (≈5 tuần) — milestone quan trọng nhất
- Attack Data Asset, combo light (3 hit), heavy, sprint attack.
- Input buffer + combo window + cancel window (xem `04_COMBAT_GAS_SPEC.md`).
- Weapon trace (sweep), damage execution, poise, hit reaction, hitstop, camera shake.
- Dodge roll với i-frame, block, parry + riposte cơ bản.
- Training dummy có máu/poise/hit react.
- **Xong khi:** đánh dummy "đã tay"; bấm nhanh không mất input; không bao giờ hit 2 lần/1 cú vung; dodge xuyên đòn có cảm giác đúng.

### M3 — Enemy đầu tiên (≈3 tuần)
- `AEclipseEnemyCharacter`, AIController, AI Perception (sight + hearing), StateTree.
- Enemy dùng **chung** hệ GAS/attack data với player.
- 1 enemy cầm kiếm: patrol → phát hiện → tiếp cận → strafe → tấn công → lùi.
- **Xong khi:** đánh 1v1 và 1v2 với enemy mà thấy công bằng, đọc được đòn.

### M4 — Vòng lặp Soulslike (≈3 tuần) — kế hoạch gốc thiếu phần này
- Rest point (kiểu bonfire): hồi máu, hồi bình máu, respawn enemy, lưu game.
- Chết → rơi tiền ("souls") tại chỗ chết → quay lại nhặt; chết lần 2 → mất.
- Bình máu (Estus-like) số lượng giới hạn.
- Save/Load với `FGuid` (enemy đã chết, cửa đã mở, shortcut, item đã nhặt).
- HUD: máu, stamina, bình máu, tiền, thanh máu enemy/boss.
- **Xong khi:** chơi → chết → nhặt tiền → rest → thoát game → vào lại đúng trạng thái.

### M5 — Boss đầu tiên (≈4 tuần)
- `AEclipseBossCharacter` + `UEclipseBossPhaseComponent` + `DA_Boss_*`.
- Fog gate, arena, thanh máu boss, 2 phase, 5–7 đòn đánh.
- Boss chết → event → mở cửa/shortcut, lưu trạng thái.
- **Xong khi:** người chơi thử (không phải bạn) thắng được sau 3–10 lần thử và muốn thử lại.

### M6 — Greybox dungeon + FUN GATE (≈3 tuần)
- 1 khu greybox 15–20 phút: 2 rest point, 1 shortcut, 8–15 enemy, 1 boss.
- Thêm 1–2 loại enemy (ví dụ: khiên, cung).
- **FUN GATE:** cho 3+ người chơi thử. Nếu không vui → quay lại M2/M3/M5 sửa. **Không đi tiếp khi chưa qua gate.**

### M7 — Equipment & Inventory (≈3 tuần)
- Inventory, 2–3 vũ khí (thẳng kiếm, greatsword, giáo), 1 khiên, 3 bộ giáp đơn giản, nhẫn (tuỳ chọn).
- Level up bằng tiền tại rest point (Vitality, Endurance, Strength, Dexterity).

### M8 — Art pipeline (≈6+ tuần)
- Pipeline Blender → Unreal được chứng minh với 1 prop, 1 modular kit, 1 nhân vật, 1 enemy.
- Thay greybox của khu M6 bằng art thật.

### M9 — VFX / Audio / UI polish → **VERTICAL SLICE**
- Gameplay Cue cho hit, block, parry, dodge; footstep theo physical material; music boss.
- Menu chính, pause, settings (graphics preset).
- Tối ưu để đạt 60 FPS High trên máy dev.

### Sau Vertical Slice (không lên lịch)
- Thêm khu vực (level riêng, nối với nhau).
- World Partition / open world — **chỉ khi** slice đã tốt và có phần cứng tốt hơn (xem ADR-008, ADR-009).
- Magic/ranged, NPC/quest, PCG, Mass AI.

---

## Tỷ lệ thời gian dự kiến
| Loại việc | Ai làm chính |
|---|---|
| C++ lõi, kiến trúc, debug | Claude (Tier A) |
| Boilerplate, data, script, doc hướng dẫn, audit | GPT Luna / Gemini Flash (Tier B) |
| Mọi thao tác trong Editor, level design, tuning, playtest | **Bạn** |
| Concept, reference sheet, icon | GPT Sol (Tier I) |

Nút thắt thật sự của dự án này là **thời gian của bạn trong Editor và Blender**, không phải tốc độ viết code. Hãy để AI làm hết phần code/doc/script để bạn dành thời gian cho tuning và art.
