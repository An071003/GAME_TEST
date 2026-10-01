# T-005 — Nghiên cứu Game Animation Sample (GASP) cho UE 5.8

| | |
|---|---|
| Status | APPROVED |
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
  1. *Dung lượng file tải chính xác:* Fab không công bố dung lượng trước khi tải; con số ~5.5–6.0 GB tải và ~11–15 GB đĩa là số liệu ước tính từ cộng đồng khi chạy sample project. Đã đồng bộ cảnh báo ổ đĩa theo [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md) (ổ C: còn ~148 GB, lưu trữ nguội dùng Google Drive Stream G: thay vì ổ ngoài, cấm đặt project/cache trên G:).
  2. *Độ tương thích skeleton UEFN_Mannequin vs SK_Mannequin:* Chưa inspect trực tiếp trong Editor 5.8; không có nguồn xác nhận các file IK Retargeter cụ thể (như giả định `RTG_UEFN_to_UE5`), cần mở Editor kiểm tra trực tiếp để quyết định dùng chung hay retarget.
  3. *Số liệu benchmark CPU Motion Matching:* Không có benchmark chính thức từ Epic cho UE 5.8; các số liệu ~0.10–0.50 ms là thảo luận không chính thức trong cộng đồng, chưa được đo đạc bằng Unreal Insights trên CPU máy dev (Intel Core i7-13620H).
- **Việc con người cần làm trong Editor:**
  1. Xác nhận dung lượng tải thực tế hiển thị trên Epic Games Launcher khi tải GASP.
  2. Mở asset skeleton `UEFN_Mannequin` trong Unreal Editor để kiểm tra bone hierarchy và xem có sẵn asset IK Retargeter không.
  3. Dùng Unreal Insights profile CPU cost thực tế khi bắt đầu đưa Player và Enemy vào màn chơi.

## Review (Tier A — Claude Opus 5.5, 2026-10-01)
- **Kết luận: APPROVED kèm đính chính.** Báo cáo đủ 7 câu + khuyến nghị, phần chưa xác minh được ghi nhãn rõ. Các đính chính dưới đây **có hiệu lực cao hơn nội dung báo cáo**; phần còn mở chuyển sang T-008 (Human kiểm tra trong project GASP tạm).
- Đã kiểm chứng trên máy (`UE_5.8/Engine/Plugins`) và trang docs Epic 5.8 (`dev.epicgames.com/.../game-animation-sample-project-in-unreal-engine`):
  1. **§4 / §5 bước 1 / Khuyến nghị 5 — sai so với hiện trạng.** `PoseSearch`, `Chooser`, `MotionWarping`, `AnimationWarping` đã bật ở T-003. `BlendStack` là dependency khai báo trong `PoseSearch.uplugin` → tự bật theo. Chỉ còn `AnimationLocomotionLibrary` (Beta) và `MotionTrajectory` (**Experimental**) là ứng viên; **chỉ bật khi Migrate báo asset GASP thật sự tham chiếu** (Lead bật, T-008/T-015).
  2. **§5 bước 6 — `CharacterTrajectoryComponent` nhiều khả năng đã lỗi thời.** Docs 5.8 mô tả trajectory được sinh bởi hàm `GenerateTrajectory` trong ABP rồi đưa vào node Pose History. Class vẫn tồn tại trong plugin `MotionTrajectory` (đánh dấu `Experimental`) nhưng không có bằng chứng GASP 5.8 dùng. → CHƯA XÁC MINH, kiểm tra ở T-008.
  3. **§5 bước 3 — tên/đường dẫn.** Docs ghi `Content/Blueprints/CBP_Sandbox_Character` (có gạch dưới), anim nằm ở `Content/Characters/UEFN_Mannequin/Animations`; thư mục con `Locomotion/` không có trong docs. Xác nhận lại trong Editor.
  4. **§6 Skeleton — docs Epic xác nhận GASP dựng trên `UEFN_Mannequin`**; nhân vật khác dùng **runtime retarget** qua `Content/Blueprints/Retargeted Characters/ABP_GenericRetarget` + biến `IKRetargeter_Map`. Điều này chạm vào **ADR-006** (chuẩn skeleton = UE5 Mannequin) → cần quyết định sau T-008 (ghi vào DECISIONS).
  5. **Nguồn:** link "Fab Standard License Terms" (`dev.epicgames.com/community/api/documentation`) không phải trang license; link Fab listing và blog trả 403 khi kiểm tra, không xác minh được. Kết luận "dùng thương mại được trong Unreal" hợp lý nhưng con người nên đọc license hiển thị trên trang Fab khi tải.
  6. **§2, §7 — số "ước tính cộng đồng" không có link** → coi như không có số liệu. Dung lượng thật đo ở T-008; CPU đo bằng Insights ở T-015.
  7. Nhỏ: link `file:///C:/...` tuyệt đối không mở được trên máy khác/GitHub → lần sau dùng link tương đối. Quy tắc cấm đặt project trên `G:` nằm ở `05_HARDWARE_AND_DISK.md` §2, không phải ADR-009.
- Quy trình: chỉ sửa đúng 2 file được phép — đạt. Lưu ý 2 commit sửa (`6f531d7`, `f83a052`) **chưa push** lên `origin`.

## Bài học
- Câu hỏi "plugin cần bật" phải kèm hiện trạng `.uproject` trong task card để agent không liệt kê lại plugin đã bật.
- Agent web-search có xu hướng điền "ước tính cộng đồng" khi không có nguồn → card sau ghi rõ "không có link = không được ghi số".
