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
  - [docs/research/GASP_UE58.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/research/GASP_UE58.md) (cập nhật gắn nhãn `[CHƯA XÁC MINH]` cho dung lượng, độ tương thích skeleton trực tiếp, và số liệu hiệu năng CPU kèm nguồn tài liệu và các bước kiểm chứng).
  - [docs/tasks/T-005-gasp-research.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/tasks/T-005-gasp-research.md) (cập nhật nội dung handoff minh bạch, giữ nguyên status REVIEW).
- **Build:** N/A (task nghiên cứu tài liệu, không thay đổi source code C++).
- **Những gì CHƯA làm / CHƯA XÁC MINH:**
  1. *Dung lượng file tải chính xác:* Fab không công bố dung lượng trước khi tải; con số ~5.5–6.0 GB tải và ~11–15 GB đĩa là số liệu ước tính từ cộng đồng khi chạy sample project.
  2. *Độ tương thích skeleton UEFN_Mannequin vs SK_Mannequin:* Chưa inspect trực tiếp trong Editor 5.8; việc GASP cung cấp sẵn IK Retargeter `RTG_UEFN_to_UE5` cho thấy có sự khác biệt giữa hai asset skeleton, cần retarget thay vì khẳng định có thể dùng chung trực tiếp 100%.
  3. *Số liệu benchmark CPU Motion Matching:* Các số liệu ~0.25 ms và ~0.50 ms là tham khảo từ bài thuyết trình kỹ thuật Unreal Fest / profiling cộng đồng; chưa benchmark thực tế bằng Unreal Insights trên CPU máy dev (Intel Core i7-13620H) và UE 5.8.
- **Việc con người cần làm trong Editor:**
  1. Xác nhận dung lượng tải thực tế hiển thị trên Epic Games Launcher khi tải GASP.
  2. Mở asset skeleton `UEFN_Mannequin` và kiểm tra asset `RTG_UEFN_to_UE5` trong Unreal Editor để quyết định dùng IK Retargeter sang `SK_Mannequin` của Eclipse.
  3. Dùng Unreal Insights profile CPU cost thực tế khi bắt đầu đưa Player và Enemy vào màn chơi.
