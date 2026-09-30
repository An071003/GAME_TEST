# Báo cáo Nghiên cứu: Game Animation Sample (GASP) cho Unreal Engine 5.8

> **Mã task:** T-005 | **Milestone:** M0 | **Dự án:** Eclipse (UE 5.8)  
> **Mục đích:** Đánh giá tính khả thi, yêu cầu kỹ thuật và phương án tích hợp locomotion Motion Matching từ Game Animation Sample vào dự án Eclipse.

---

## 1. Bản phát hành cho UE 5.8 & Tên trên Fab
- **Trạng thái hỗ trợ UE 5.8:** **ĐÃ CÓ BẢN CHÍNH THỨC**. Epic Games phát hành bản cập nhật cho UE 5.8 bổ sung Physics Control, ragdoll và multi-character pose search.
- **Tên chính xác trên Fab:** `Game Animation Sample` (phát hành bởi Epic Games).
- **Fab Listing ID:** `880e319a-a59e-4ed2-b268-b32dac7fa016`
- **Ngày cập nhật UE 5.8:** Ngày 12 tháng 08 năm 2026.
- **Nguồn xác minh:**
  - [Fab Listing: Game Animation Sample](https://www.fab.com/listings/880e319a-a59e-4ed2-b268-b32dac7fa016)
  - [Unreal Engine Blog: Download the latest Game Animation Sample Project updated for UE 5.8](https://www.unrealengine.com/tech-blog/download-the-latest-game-animation-sample-project-now-updated-for-ue-5-8)
  - [Epic Developer Community Documentation: Game Animation Sample Project in Unreal Engine 5.8](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine)

---

## 2. Dung lượng tải về và dung lượng đĩa
- **Trạng thái:** **[CHƯA XÁC MINH - KHÔNG TÌM THẤY NGUỒN CHÍNH THỨC CÔNG BỐ DUNG LƯỢNG]**
  - Trang Fab của Game Animation Sample không hiển thị kích thước file tải hay dung lượng chiếm dụng trên đĩa.
  - **Số liệu ước tính từ cộng đồng:**
    - Dung lượng tải về (Vault Cache): Ước tính khoảng **~5.5 GB – 6.0 GB**.
    - Dung lượng thư mục project mẫu sau khi tạo: Khoảng **~5.5 GB – 6.0 GB**.
    - Bộ nhớ đệm Derived Data Cache (DDC) khi mở project lần đầu: Khoảng **~3.0 GB – 5.0 GB**.
    - Tổng dung lượng ước tính nếu giữ cả Vault Cache và project mẫu: Khoảng **~11.0 GB – 15.0 GB**.
    - *Lưu ý: Các con số trên là ước tính truyền miệng từ người dùng cộng đồng khi chạy sample project UE5, hoàn toàn chưa có tài liệu hay công bố chính thức từ Epic Games.*
- **Cảnh báo phần cứng & lưu trữ (đối chiếu [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md)):**
  - Ổ C: máy dev hiện còn **~148 GB trống** (ngân sách an toàn duy trì ở mức 113 GB).
  - Dự án hiện sử dụng **Google Drive for desktop (gói 5 TB, chế độ Stream, ổ `G:`)** cho lưu trữ nguội (ArtSource, backup, archive build).
  - **Quy tắc bắt buộc từ doc 05:** Tuyệt đối **KHÔNG** tạo project GASP hay đặt DDC vào ổ Google Drive `G:` (client đồng bộ cloud sẽ khóa hoặc xung đột file).
  - Phương án đề xuất: Tạo project GASP tạm thời trên một thư mục tạm trên ổ C:, sau khi migrate các asset cần thiết vào `Unreal/Content` thì xóa project mẫu tạm thời để giải phóng dung lượng.
- **Hành động kiểm chứng (Con người):** Xem trực tiếp dung lượng file download hiển thị tại dialog của Epic Games Launcher khi bấm tải về.
- **Nguồn:**
  - [Fab Listing: Game Animation Sample](https://www.fab.com/listings/880e319a-a59e-4ed2-b268-b32dac7fa016) *(Trang listing chính thức trên Fab; không công bố dung lượng file tải)*

---

## 3. Bản quyền (License) & Khả năng dùng cho game thương mại
- **Khả năng dùng thương mại:** **HOÀN TOÀN ĐƯỢC PHÉP DÙNG CHO GAME THƯƠNG MẠI**.
- **Hình thức cấp phép:** Phân phối miễn phí theo **Epic Content License Agreement** / **Fab Standard License**.
- **Điều kiện ràng buộc cốt lõi:**
  - **Chỉ sử dụng trong hệ sinh thái Unreal Engine:** Không được trích xuất dữ liệu animation/mesh để sử dụng trong các engine khác (như Unity, Godot).
  - Không phát sinh thêm phí bản quyền riêng cho pack asset này. Doanh thu của game tuân theo ngưỡng miễn bản quyền chuẩn của Unreal Engine EULA (5% sau khi doanh thu tổng vượt $1,000,000 USD).
- **Nguồn xác minh:**
  - [Unreal Engine EULA](https://www.unrealengine.com/eula)
  - [Fab Standard License Terms](https://dev.epicgames.com/community/api/documentation)

---

## 4. Danh sách Plugin yêu cầu bật
Để đưa hệ thống Motion Matching locomotion của GASP vào Eclipse mà không làm phình project, danh sách plugin được chia làm 2 nhóm:

### A. Nhóm bắt buộc để chạy Locomotion Motion Matching (Cốt lõi cho Eclipse)
1. `PoseSearch` — Runtime Motion Matching, Pose Search Schemas và Pose Search Databases.
2. `Chooser` — Chooser Tables để lọc database hoạt ảnh dựa trên gameplay context/tags.
3. `MotionTrajectory` — Sinh và dự đoán quỹ đạo di chuyển (Trajectory Query).
4. `AnimationWarping` — Hỗ trợ Orientation Warping, Steering, Offset Root Bone.
5. `MotionWarping` — Warp root motion tới mục tiêu.
6. `AnimationLocomotionLibrary` — Các thuật toán bổ trợ locomotion và Distance Matching.
7. `BlendStack` — Quản lý chuyển đổi động giữa các hoạt ảnh trong Pose Search.

### B. Nhóm bổ trợ trong project mẫu GASP (Cân nhắc KHÔNG bật ở Eclipse)
- `Mover` — Hệ thống di chuyển mới (Eclipse dùng CharacterMovementComponent chuẩn).
- `PhysicsControl` — Ragdoll motors động (mới thêm ở 5.8).
- `SmartObjects`, `GameplayInteractions`, `ContextualAnimation` — Phục vụ hệ thống Traversal leo trèo/vượt vật cản. *(Lưu ý: [DECISIONS.md ADR-009](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/DECISIONS.md#adr-009) cấm bật `SmartObjects` ở giai đoạn đầu).*
- `RigLogic`, `LiveLinkControlRig`, `DeformerGraph` — Dành riêng cho MetaHuman.
- `DrawDebugLibrary`, `AnimationCurveExpression` — Debug editor utility.
- **Nguồn xác minh:**
  - [Epic Docs: Game Animation Sample Project AnimGraph](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine#animgraph)
  - [Unreal Engine Blog: UE 5.8 Feature List](https://www.unrealengine.com/tech-blog/download-the-latest-game-animation-sample-project-now-updated-for-ue-5-8)

---

## 5. Quy trình Migrate Locomotion sang Project khác
Theo hướng dẫn của Epic và thực tiễn cộng đồng, quy trình thực hiện gồm 6 bước:

1. **Chuẩn bị Project đích (Eclipse):** Bật 7 plugin cốt lõi nêu ở mục 4A trong `Unreal/Eclipse.uproject`, lưu và restart Editor.
2. **Tạo Project GASP tạm thời:** Tải và tạo project GASP từ Epic Games Launcher / Fab vào một thư mục tạm ngoài repo (hoặc ổ ngoài).
3. **Xác định các Asset cần chuyển:**
   - Animation Blueprint: `Content/Blueprints/ABP_SandboxCharacter`
   - Dữ liệu Motion Matching: `Content/Characters/UEFN_Mannequin/Animations/MotionMatchingData/` (chứa Chooser Table `CHT_PoseSearchDatabases`, các `PSD_*`, và Search Schemas).
   - Animation Sequences cần dùng: `Content/Characters/UEFN_Mannequin/Animations/Locomotion/` (Walk, Run, Sprint, Stops, Pivots, Starts).
4. **Thực hiện Migrate qua Editor:**
   - Trong Content Browser của GASP, chuột phải vào `ABP_SandboxCharacter` (hoặc thư mục chọn lọc) $\rightarrow$ **Asset Actions** $\rightarrow$ **Migrate...**.
   - Trình Migrate sẽ tự động gom các asset phụ thuộc (Skeleton, Bones, Curves, Chooser).
   - Chọn đường dẫn đích là thư mục `Content` của project `Eclipse`.
5. **Đồng bộ Project Settings:**
   - Sao chép các Gameplay Tags liên quan tới locomotion (trạng thái di chuyển, gait) sang `DefaultGameplayTags.ini` của Eclipse.
   - Chạy **Fix Up Redirectors in Folder** trong thư mục Content của Eclipse.
6. **Tích hợp vào Character:**
   - Thêm `CharacterTrajectoryComponent` vào Character Blueprint của người chơi.
   - Gán `ABP_SandboxCharacter` (hoặc subclass đã đổi tên thành `ABP_EclipseCharacter`) vào Skeletal Mesh.
- **Nguồn xác minh:**
  - [Epic Developer Community: Migrating Assets in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/migrating-assets-in-unreal-engine)
  - [Epic Docs: Game Animation Sample Project Walkthrough](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine#exportinganimations)

---

## 6. Phân tích Skeleton của GASP
- **Tên asset Skeleton:** `UEFN_Mannequin` (nằm tại thư mục `Content/Characters/UEFN_Mannequin/`).
- **Cấu trúc xương:** Dựa trên cấu trúc xương của UE5 Mannequin (Pelvis, Spine, Clavicle, Limbs, các xương IK `ik_foot_root`, `ik_hand_root`...).
- **Trạng thái tương thích & Retargeter:** **[CHƯA XÁC MINH TRỰC TIẾP TRONG EDITOR]**
  - **Sự thật đã xác minh:** GASP sử dụng asset skeleton có tên `UEFN_Mannequin` nằm tại thư mục `Characters/UEFN_Mannequin/` (thay vì file `SK_Mannequin` mặc định của mẫu Third Person).
  - **Điểm CHƯA XÁC MINH:**
    - Chưa xác minh tên cụ thể của các file IK Rig / IK Retargeter trong project GASP (các tên giả định như `RTG_UEFN_to_UE5` hay `RTG_UEFN_to_UE4` hoàn toàn **chưa có nguồn tài liệu chính thức xác nhận**).
    - Chưa xác minh mức độ sai khác về bind pose, bone proportions, hay danh sách twist bones giữa `UEFN_Mannequin` và `SK_Mannequin` chuẩn UE5.
    - Cả hai kết luận trước đây ("khớp 100% gắn mesh không cần retarget" HOẶC "chắc chắn có sẵn asset Retargeter RTG_UEFN_to_UE5") đều là suy đoán chưa được kiểm chứng trong Editor.
  - **Hành động kiểm chứng (Con người):**
    1. Khi tải project GASP, mở Content Browser kiểm tra xem Epic có cung cấp sẵn IK Retargeter cho `UEFN_Mannequin` không.
    2. So sánh asset skeleton `UEFN_Mannequin` với `SK_Mannequin` trong Editor để xác định phương án: gán chung skeleton (Compatible Skeleton) hay tạo IK Retargeter để xuất animation sang `SK_Mannequin` của Eclipse theo quy trình chuẩn của UE5.
- **Nguồn xác minh:**
  - [Epic Developer Community: IK Rig and Retargeting in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/ik-rig-animation-retargeting-in-unreal-engine) *(Tài liệu nguyên lý quy trình Retarget trong UE5; không liệt kê tên asset cụ thể của GASP)*
  - [Epic Docs: Game Animation Sample Project Walkthrough](https://dev.epicgames.com/documentation/en-us/unreal-engine/game-animation-sample-project-in-unreal-engine)

---

## 7. Đánh giá Hiệu năng & Chi phí CPU (Motion Matching)
- **Trạng thái:** **[CHƯA XÁC MINH - KHÔNG CÓ NGUỒN BENCHMARK CHÍNH THỨC CHO UE 5.8]**
  - Epic Games không công bố bảng số liệu benchmark cố định (mili-giây) cho Pose Search trong tài liệu chính thức.
  - **Số liệu thảo luận cộng đồng (chưa kiểm chứng):** Khoảng ~0.10 ms – 0.50 ms / frame trên Worker Thread cho Pose Selection (so với ~0.008 ms của State Machine đơn giản) chỉ là các con số thảo luận trong các bài chia sẻ kinh nghiệm cộng đồng dev UE5, phụ thuộc mạnh vào cấu hình máy, kích thước database và số channel trong schema.
- **Rủi ro kỹ thuật cho Eclipse:**
  - Máy dev dùng CPU Intel Core i7-13620H (10C/16T). Mục tiêu [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md) là **Game thread $\le$ 6 ms**.
  - Không thể giả định hiệu năng an toàn dựa trên số liệu thảo luận khi chưa profile thực tế trên máy dev, đặc biệt khi spawn 5–10 AI Enemy đồng thời.
- **Biện pháp tối ưu đề xuất (từ tài liệu tối ưu của Epic):**
  1. Phân vùng Database bằng **Chooser Table** (chỉ query database nhỏ tương ứng với trạng thái hiện tại).
  2. Bật **Animation Update Rate Optimization (URO)** để giảm tần suất tick animation của enemy ở xa.
  3. Sử dụng Database LOD hoặc chuyển AI quái thường sang State Machine truyền thống.
- **Hành động kiểm chứng (Tier A / Con người):** Bắt buộc dùng **Unreal Insights** (kênh `Cpu`, `Animation`) trực tiếp trên máy dev khi tích hợp locomotion để đo đạc thông số thực tế trước khi chốt kiến trúc cho AI.
- **Nguồn xác minh:**
  - [Epic Docs: Animation Debugging and Optimization in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/animation-debugging-and-optimization-in-unreal-engine) *(Tài liệu chính thức về công cụ và phương pháp tối ưu URO/LOD; không đưa ra số liệu benchmark mili-giây cố định)*

---

## 8. Khuyến nghị cho Eclipse (≤ 10 dòng)
1. **Dùng GASP cho Player Locomotion:** Hướng đi đúng (ADR-007), miễn phí bản quyền thương mại theo Fab Standard License.
2. **Kiểm tra Skeleton trong Editor:** Mở asset `UEFN_Mannequin` trong Editor để kiểm tra cấu trúc; xác định xem có sẵn Retargeter hay cần tạo IK Retargeter sang `SK_Mannequin` của Eclipse.
3. **Không tạo project hay lưu cache trên Google Drive:** Tạo project GASP tạm trên ổ C: để migrate, không lưu trữ trên Google Drive Stream `G:` (tránh lỗi đồng bộ cloud theo ADR-009 và doc 05).
4. **Chỉ migrate locomotion cốt lõi:** Chỉ lấy `ABP_SandboxCharacter`, Chooser Table và database locomotion; không migrate Mover hay Traversal.
5. **Chỉ bật 7 plugin cốt lõi:** Bật 7 plugin nhóm 4A trong `Eclipse.uproject`.
6. **Benchmark hiệu năng bằng Unreal Insights:** Không áp dụng Motion Matching cho quái thường nếu chưa profile thực tế trên máy dev; dự phòng dùng State Machine + URO cho Enemy.
