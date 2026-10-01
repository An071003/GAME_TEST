# T-007 — Mood board + art direction cho khu dungeon đầu tiên (`L_Dungeon01`)

| | |
|---|---|
| Status | REVIEW |
| Milestone | M0 (không chặn M1) |
| Tier | I |
| Gợi ý model | GPT 6.1 Sol |
| Phụ thuộc | — |
| Branch | `task/T-007-dungeon01-moodboard` |

## Mục tiêu
Có 6 ảnh concept cùng một phong cách và một trang art direction ngắn để chủ dự án chốt "cảm giác" khu dungeon đầu tiên. Từ M6 trở đi, greybox và kit modular (M8) sẽ bám theo trang này.

## Đọc trước
- `AGENTS.md`, `docs/06_ART_PIPELINE.md` §5 (mẫu prompt, nơi lưu ảnh)
- `docs/00_MASTER_PLAN.md` (Vertical Slice: dungeon liên kết, shortcut, rest point, 1 boss)
- `docs/03_CONVENTIONS.md` §4 (hành lang ≥ 300 cm, cửa 220–300 cm, nhân vật ~180 cm)

## Brief (hướng khởi đầu — chủ dự án có thể đổi khi review)
- **Chủ đề:** pháo đài-ngục bỏ hoang, nửa chìm vào vách núi đá. Kẻ canh giữ cuối khu là boss **"the Warden"**. Kẻ thù thường là **"Hollow"**: tù nhân/lính canh đã mất trí. (Hai tên này lấy từ tên placeholder `DA_Boss_Warden`, `DA_Enemy_Hollow_*` đã có trong tài liệu.)
- **Tone:** dark medieval fantasy, thực tế, u ám nhưng **đọc được**: người chơi luôn thấy đường đi chính và kẻ thù.
- **Bảng màu:** đá xám lạnh, gỉ sắt, gỗ mục làm nền; **một màu ấm duy nhất** (lửa/đuốc, rest point) để dẫn đường.
- **Vật liệu chính:** đá khối lớn, sắt rèn (song sắt, xích, cửa), gỗ mục, rêu và nước đọng. Các vật liệu này phải làm được bằng **kit modular** (tường, sàn, vòm, cầu thang, cột).
- **Ràng buộc gameplay:** hành lang rộng (≥ 3 m) cho camera và lock-on; trần đủ cao; không rối mắt ở tầm nhân vật; boss arena là không gian tròn hoặc vuông, rộng, ít vật cản.

## 6 ảnh cần tạo
| # | Tên file | Nội dung |
|---|---|---|
| 01 | `Dungeon01_Approach_v01.png` | Lối vào pháo đài nhìn từ xa, thấy được quy mô và vách núi |
| 02 | `Dungeon01_Hall_v01.png` | Sảnh/khu giam chính, nhiều tầng, đường đi chính rõ |
| 03 | `Dungeon01_Corridor_v01.png` | Hành lang chiến đấu điển hình (có Hollow nhỏ phía xa để thấy tỉ lệ) |
| 04 | `Dungeon01_Shortcut_v01.png` | Shortcut: thang máy xích hoặc cửa sắt mở một chiều |
| 05 | `Dungeon01_RestPoint_v01.png` | Rest point: nguồn sáng ấm duy nhất trong phòng tối |
| 06 | `Dungeon01_BossArena_v01.png` | Arena của Warden phía sau fog gate |

Mọi ảnh dùng **cùng khối `[STYLE]`** trong `06_ART_PIPELINE.md` §5, chỉ thay `[SUBJECT]`/`[VIEW]`. `[VIEW]` của mood board là góc nhìn người chơi (third-person, eye-level), **không** dùng orthographic. Ảnh ngang 16:9. Không chữ, không watermark.

## Được phép sửa / tạo
- `docs/art/Dungeon01_ArtDirection.md` (tạo mới)
- Ảnh và file prompt `.txt` cùng tên trong `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\` (**ngoài repo**, ADR-009)
- Task card này (Handoff)

## Cấm
- **Không** commit ảnh vào repo (không `.png` nào trong `docs/` hay `Unreal/`).
- Không sửa file nào khác.

## Các bước
1. Tạo 6 ảnh theo bảng. Mỗi ảnh lưu kèm `<tên>.txt` chứa **nguyên văn** prompt đã dùng. Nếu không ghi được vào `G:` thì đưa ảnh và prompt cho chủ dự án lưu tay, và ghi vào Handoff.
2. Viết `docs/art/Dungeon01_ArtDirection.md` (tiếng Việt, ≤ 1 trang) gồm các mục:
   - **Một câu tóm tắt** cảm giác khu vực.
   - **Bảng màu:** 5–7 màu hex lấy từ ảnh, ghi vai trò (nền / nhấn / dẫn đường).
   - **Vật liệu & kit modular:** liệt kê các mảnh kit cần có (tên tạm theo `03_CONVENTIONS.md`, ví dụ `SM_Dungeon_Wall_A`).
   - **Ánh sáng:** nguồn sáng chính, màu, lưu ý cho máy 6 GB VRAM (ít đèn động, dùng Lumen mặc định).
   - **Đọc được (readability):** cách dẫn đường bằng ánh sáng và hình khối.
   - **Danh sách 6 ảnh:** đường dẫn trên `G:` + một dòng mô tả mỗi ảnh. **Không nhúng ảnh.**
3. Điền Handoff, đổi Status thành `REVIEW`.

## Tiêu chí hoàn thành (kiểm tra được)
- [x] 6 ảnh + 6 file `.txt` có trong `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\`, đặt tên đúng bảng.
- [x] Phần `[STYLE]` trong 6 file `.txt` giống hệt nhau.
- [x] `docs/art/Dungeon01_ArtDirection.md` có đủ 6 mục ở bước 2.
- [ ] `git diff --stat main` chỉ có `docs/art/Dungeon01_ArtDirection.md` và task card này; không có file `.png`.
- [ ] Chủ dự án xem và chọn: giữ hướng này / chỉnh / làm lại (ghi ở mục Review).

## Câu hỏi / Blocker
- Tiêu chí `git diff --stat main` chỉ có 2 file chưa đạt do lịch sử branch có sẵn thay đổi T-006 ở `Tools/check_disk.sh`, `docs/THIRD_PARTY.md`, `docs/tasks/BACKLOG.md`, `docs/tasks/T-006-third-party-disk-script.md`. Đã có trước khi làm T-007 (HEAD ban đầu: `ea04098359fc041416a1d6ff6cc227ea392011a7`). Không sửa các file này; Lead cần tách lịch sử branch khi chuẩn bị merge nếu vẫn yêu cầu diff với `main` chỉ có T-007.

---
## Handoff
- Ảnh đã tạo: đủ 6 PNG và 6 prompt `.txt` nguyên văn tại `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\`: `Dungeon01_Approach_v01`, `Dungeon01_Hall_v01`, `Dungeon01_Corridor_v01`, `Dungeon01_Shortcut_v01`, `Dungeon01_RestPoint_v01`, `Dungeon01_BossArena_v01`. Đường dẫn từng ảnh ghi trong art direction.
- Công cụ: imagegen tích hợp, một lượt tạo riêng cho mỗi ảnh. Khối `[STYLE]` giữ nguyên văn từ `06_ART_PIPELINE.md` §5; phần chung của các prompt giống nhau, chỉ `[SUBJECT]` và `[VIEW]` thay đổi. File `.txt` không thêm ghi chú hậu xử lý.
- Hậu xử lý đã được chủ dự án cho phép trong chat: ảnh gốc 1672×941 cắt 4 px mỗi bên, 2 px trên và 3 px dưới thành **1664×936, đúng 16:9**; không đổi nội dung hay co giãn. Bản gốc của công cụ vẫn được giữ ngoài repo.
- Worktree riêng: checkout chung chuyển sang T-010 trong lúc tạo ảnh; phần tài liệu T-007 được hoàn tất tại `C:\Users\ADMIN\.codex\worktrees\t-007-dungeon01-moodboard\GAME_TEST` trên nhánh `task/T-007-dungeon01-moodboard`.
- File trong repo: tạo `docs/art/Dungeon01_ArtDirection.md`; cập nhật card này (Status, checklist, Blocker, Handoff). Không có ảnh hoặc prompt trong repo.
- Build: **N/A** — task chỉ tạo concept và tài liệu, không thay đổi C++/config/asset Unreal; không chạy build.
- Kiểm tra: PASS cho tên/đủ 12 file, kích thước 6 ảnh, nguyên văn 6 prompt, `[STYLE]` giống hệt nhau; đã xem từng ảnh và kiểm tra bố cục, vật liệu, tuyến đi, Hollow/rest point/Warden. Bảng 7 màu lấy từ pixel ảnh cuối; art direction có đủ 6 mục và không nhúng ảnh.
- Giới hạn diff: phần làm thêm của T-007 chỉ có 2 file cho phép; diff toàn branch với `main` còn các file T-006 có sẵn nêu ở Blocker. Không tự đổi lịch sử branch.
- **CHƯA XÁC MINH:** kích thước thật của hành lang/cửa/trần/arena, khoảng trống camera/lock-on và hiệu năng 6 GB VRAM. Concept phối cảnh là tham chiếu cảm giác; các thông số phải kiểm tra bằng greybox và đo trong Editor ở M6/M8. Hollow/Warden là hình tham chiếu placeholder, chưa chốt thiết kế nhân vật.
- Chưa làm: chủ dự án + Tier A review và chọn giữ/chỉnh/làm lại; để mục Review trống. Không có thao tác Unreal Editor cần làm trong T-007.
- Việc chủ dự án cần làm:
  1. Mở thư mục ảnh trên `G:` và xem đủ 6 ảnh cùng trang art direction.
  2. Chọn giữ hướng này / chỉnh / làm lại, ghi kết luận và yêu cầu cụ thể vào Review.

## Review (chủ dự án + Tier A)
- Kết luận:
