# T-008 — Kiểm tra GASP 5.8 trong project tạm (đóng các điểm CHƯA XÁC MINH của T-005)

| | |
|---|---|
| Status | REVIEW |
| Milestone | M0 |
| Tier | Human (tải, mở Editor) + A (Claude đọc file trên đĩa, viết kết luận) |
| Gợi ý model | Bạn + Opus 5.5 |
| Phụ thuộc | T-005 (APPROVED) |
| Không chạy song song với | T-004 (cùng dùng ổ đĩa/DDC — làm T-004 trước nếu được) |
| Branch | `task/T-008-gasp-inspect` |

## Mục tiêu
Có số liệu thật về GASP 5.8 trên máy dev (dung lượng, plugin, skeleton, trajectory, FPS cơ bản) để Claude chốt cách xử lý skeleton (ADR-006) và viết hướng dẫn T-015.

## Đọc trước
- `docs/tasks/T-005-gasp-research.md` mục **Review** (đính chính)
- `docs/05_HARDWARE_AND_DISK.md` §2 (không đặt project trên `G:`)

## Được phép sửa / tạo
- Task card này (Handoff)
- `docs/research/GASP_UE58.md` (Claude bổ sung mục "Kiểm chứng T-008")
- `docs/DECISIONS.md` mục "Đề xuất chờ duyệt" (Claude ghi đề xuất về ADR-006)
- **Không** thêm gì vào `Unreal/` của Eclipse trong task này.

## Các bước
### Human (≈30 phút thao tác + thời gian tải/compile shader)
1. Ghi lại dung lượng trống ổ C: trước khi tải (`Tools/check_disk.sh` nếu T-006 đã xong, không thì Explorer).
2. Epic Games Launcher → Fab Library (hoặc fab.com) → **Game Animation Sample** → chọn phiên bản **5.8** → Create Project.
   - Thư mục: `C:\UE_Temp\` (tạo mới; **không** nằm trong `GAME_TEST`, **không** trên `G:`). Tên: `GASP58`.
   - Ghi lại dung lượng tải mà Launcher hiển thị và **license** ghi trên trang Fab.
3. Mở `C:\UE_Temp\GASP58\GASP58.uproject`, chờ compile shader xong (có thể lâu). Engine Scalability = High.
4. Bấm Play (PIE) trong map mặc định, chạy/đi bộ/sprint ~1 phút, gõ console `stat unit` → chụp màn hình (Frame / Game / Draw / GPU).
5. Đóng Editor. Nhắn Claude: **"T-008: đã tạo xong GASP58"**.

### Claude (đọc file, không cần Editor)
6. Đọc `GASP58.uproject` → danh sách plugin thật.
7. Liệt kê `Content/` → đường dẫn thật của ABP, CBP, Chooser, PSD, skeleton, các `RTG_*`/`IK_*`, có Manny/Quinn hay không.
8. Tìm chuỗi tên class trong `.uasset` (name table) để xác định GASP có dùng `CharacterTrajectoryComponent` hay không, ABP/CBP tham chiếu plugin nào.
9. Đo `du -sh` project, DDC/Zen; ghi vào báo cáo.
10. Viết mục "Kiểm chứng T-008" trong `docs/research/GASP_UE58.md` + đề xuất skeleton vào `DECISIONS.md` ("Đề xuất chờ duyệt"), ví dụ các phương án:
    - (a) Player dùng `UEFN_Mannequin` làm skeleton chuẩn (không retarget runtime),
    - (b) Giữ UE5 Manny, retarget **offline** dataset GASP sang Manny,
    - (c) Runtime retarget qua `ABP_GenericRetarget`.
    Kèm chi phí dung lượng/CPU của từng phương án. **Chủ dự án chọn.**

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] Handoff có: dung lượng tải, dung lượng project trên đĩa, license, ảnh/số `stat unit`.
- [ ] `docs/research/GASP_UE58.md` có mục "Kiểm chứng T-008" với danh sách plugin thật + đường dẫn asset thật.
- [ ] `DECISIONS.md` có đề xuất về skeleton, chủ dự án đã chọn phương án.
- [ ] Ghi chú: giữ hay xoá `C:\UE_Temp\GASP58` (giữ tới khi T-015 migrate xong, rồi xoá).

## Câu hỏi / Blocker
_(ghi vào đây nếu dừng)_

---
## Handoff
- Dung lượng tải (Launcher):
- License (trang Fab):
- Dung lượng ổ C trước / sau:
- `stat unit` (Frame / Game / Draw / GPU):
- Ghi chú khác:

## Review (Tier A điền)
- Kết luận:

## Kết quả (Claude, 2026-10-01)
- Dung lượng tải: **CHƯA GHI** (chủ dự án chưa báo số trong Launcher). Project 7.2 GB, ổ C: 148 → 132 GB.
- License (trang Fab): **CHƯA GHI** — chủ dự án chép dòng license từ trang Fab vào `THIRD_PARTY.md` (T-006).
- `stat unit` (ảnh chủ dự án gửi): Frame 16.67 / Game 7.97 / Draw 4.41 / GPU 8.47 ms, VRAM 3.34/5.03 GB — chi tiết và hạn chế ở báo cáo §9.6.
- Báo cáo đầy đủ: `docs/research/GASP_UE58.md` §9. Đề xuất skeleton: `docs/DECISIONS.md` "Đề xuất #1" (chờ chủ dự án chọn).
- Phát hiện chính: không cần bật plugin thêm; không dùng `CharacterTrajectoryComponent`; migrate chỉ `SandboxCharacter_CMC_ABP`, không migrate character BP; Game thread 7.97 ms đã vượt budget 6 ms (chưa tối ưu, trong Editor).
- CHƯA XÁC MINH (để T-015): so sánh bone tree trong Editor; dependency thật của ABP trong dialog Migrate; montage combat chạy ở skeleton nào khi dùng retarget runtime; chi phí CPU Motion Matching tách riêng.
- Tiêu chí còn thiếu: dung lượng tải + license; chủ dự án chọn phương án skeleton.
