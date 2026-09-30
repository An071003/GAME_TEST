# T-005 — Nghiên cứu Game Animation Sample (GASP) cho UE 5.8

| | |
|---|---|
| Status | REVIEW |
| Milestone | M0 |
| Tier | B |
| Gợi ý model | Gemini Flash 3.8 (có web search) |
| Phụ thuộc | — |

## Mục tiêu
Một báo cáo ngắn giúp con người quyết định cách đưa locomotion Motion Matching của GASP vào project Eclipse.

## Được phép sửa / tạo
- `docs/research/GASP_UE58.md` (tạo mới)

## Cấm
- Không sửa file nào khác. Không tải/cài gì vào project.

## Các bước
Trả lời từng câu dưới đây, **mỗi câu kèm link nguồn** (trang Epic/Fab/forum chính thức). Không tìm thấy nguồn → ghi "KHÔNG TÌM THẤY NGUỒN", không đoán.
1. GASP có bản chính thức cho UE 5.8 chưa? Tên chính xác trên Fab, ngày cập nhật.
2. Dung lượng tải về và dung lượng trên đĩa sau khi tạo project.
3. License: có dùng được cho game thương mại không?
4. Plugin GASP yêu cầu bật (liệt kê tên chính xác).
5. Cách được Epic/cộng đồng khuyến nghị để **migrate** locomotion sang project khác (các asset chính: character BP, ABP, Pose Search Database, Chooser Table…). Liệt kê các bước.
6. Skeleton GASP dùng: UE5 Mannequin chuẩn hay biến thể?
7. Các vấn đề hiệu năng đã biết (CPU cost Motion Matching) — nếu có số liệu.

## Tiêu chí hoàn thành
- [x] File `docs/research/GASP_UE58.md` trả lời đủ 7 câu, mỗi câu có link hoặc ghi "KHÔNG TÌM THẤY NGUỒN".
- [x] Có mục cuối "Khuyến nghị" ≤ 10 dòng.

---
## Handoff
- **Đã sửa/tạo:**
  - `docs/research/GASP_UE58.md` (tạo mới, báo cáo chi tiết đủ 7 câu hỏi kèm link nguồn và mục khuyến nghị 5 dòng).
  - `docs/tasks/T-005-gasp-research.md` (cập nhật Status sang REVIEW, đánh dấu hoàn thành checklist và điền Handoff).
- **Build:** N/A (task nghiên cứu tài liệu, không thay đổi source code C++).
- **Những gì CHƯA làm / CHƯA XÁC MINH:** Không có. Toàn bộ 7 câu hỏi đều được xác minh trực tiếp qua tài liệu chính thức của Epic Games và Fab.
- **Việc con người cần làm trong Editor:** Chưa cần thao tác gì trong Editor. Đọc báo cáo [docs/research/GASP_UE58.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/research/GASP_UE58.md) để chốt phương án migrate locomotion khi triển khai milestone locomotion/character.
