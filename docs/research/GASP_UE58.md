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
- **Trạng thái:** **[CHƯA XÁC MINH CHÍNH XÁC]** — Nguồn Fab không hiển thị kích thước file tải trước khi thêm vào launcher.
- **Số liệu ước tính (tham khảo từ cộng đồng khi chạy sample project UE5):**
  - **Dung lượng tải về (Vault Cache qua Epic Games Launcher):** Ước tính khoảng **~5.5 GB – 6.0 GB**.
  - **Dung lượng trên đĩa sau khi tạo project:**
    - Thư mục project mẫu (`Content/`, `Config/`, `Source/`): Khoảng **~5.5 GB – 6.0 GB**.
    - Bộ nhớ đệm Derived Data Cache (DDC) sinh ra khi mở và compile animation database lần đầu: Khoảng **~3.0 GB – 5.0 GB**.
    - **Tổng dung lượng đĩa ước tính nếu giữ cả Vault Cache và project mẫu:** Khoảng **~11.0 GB – 15.0 GB**.
- **Quy tắc chung của Epic Games:** Các sample project độ phức tạp cao kèm nhiều animation dữ liệu lớn thường yêu cầu dự phòng từ **20 GB – 30 GB SSD** để unpack, build DDC và compile shader ổn định.
- **Cảnh báo phần cứng (đối chiếu [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md)):** Ổ C máy dev hiện chỉ còn ~113 GB trống. Việc tải cả project vào ổ C có thể chiếm 10%–15% dung lượng còn lại. Bắt buộc tạo project ở thư mục tạm hoặc ổ ngoài, chỉ migrate asset cần thiết vào `Unreal/Content` (tuân thủ ADR-009).
- **Hành động kiểm chứng (Con người):** Xác nhận dung lượng download thực tế hiển thị trên Epic Games Launcher khi bấm tải về.
- **Nguồn xác minh:**
  - [Fab Listing: Game Animation Sample](https://www.fab.com/listings/880e319a-a59e-4ed2-b268-b32dac7fa016)
  - [Epic Games Launcher Storage Recommendations](https://dev.epicgames.com/documentation/en-us/unreal-engine/installing-unreal-engine)

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
- **Cấu trúc xương:** Dựa trên cấu trúc xương chuẩn của UE5 Mannequin (Pelvis, Spine, Clavicle, Limbs, các xương IK `ik_foot_root`, `ik_hand_root`...).
- **Trạng thái tương thích:** **[CHƯA XÁC MINH TRỰC TIẾP TRONG EDITOR]**
  - **Sự thật đã biết:** `UEFN_Mannequin` là một asset skeleton riêng biệt, không phải cùng một asset file `SK_Mannequin` mặc định của UE5. Trong project GASP, Epic cung cấp sẵn IK Retargeter (`RTG_UEFN_to_UE5` và `RTG_UEFN_to_UE4`), điều này cho thấy có sự khác biệt nhất định về bind pose, bone proportions hoặc danh sách twist bones giữa 2 hệ xương.
  - **Kết luận cần đính chính:** Nhận định trước đây cho rằng *"hoàn toàn đồng nhất 100% và mesh Blender theo SK_Mannequin có thể gắn trực tiếp không cần retarget"* là **chưa được kiểm chứng thực tế trong Unreal Editor 5.8**.
  - **Hành động kiểm chứng (Con người):**
    1. Khi tải project GASP, mở asset skeleton `UEFN_Mannequin` và kiểm tra bone tree so với `SK_Mannequin`.
    2. Kiểm tra asset `RTG_UEFN_to_UE5` có sẵn trong GASP: nếu cần, phương án an toàn nhất theo chuẩn của Epic là dùng chính Retargeter này để chuyển toàn bộ locomotion animation sang `SK_Mannequin` của Eclipse thay vì ép dùng chung skeleton asset.
- **Nguồn xác minh:**
  - [Epic Docs: Adding a MetaHuman to the Game Animation Sample Project](https://dev.epicgames.com/documentation/en-us/unreal-engine/adding-a-metahuman-to-the-game-animation-sample-project-in-unreal-engine)
  - [Epic Developer Community: IK Rig and Retargeting in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/ik-rig-animation-retargeting-in-unreal-engine)

---

## 7. Đánh giá Hiệu năng & Chi phí CPU (Motion Matching)
- **Trạng thái:** **[CHƯA XÁC MINH TRÊN MÁY DEV / UE 5.8 - SỐ LIỆU THAM KHẢO TỪ PROFILING CỘNG ĐỒNG]**
- **Số liệu tham khảo (từ các bài thuyết trình kỹ thuật Unreal Fest & profiling cộng đồng):**
  - Chi phí Pose Selection trên Worker Thread: Dao động khoảng **~0.10 ms – 0.50 ms / character / frame** (tùy thuộc vào số channels trong `PoseSearchSchema` và số poses trong database).
  - So sánh: Bước tìm kiếm pose đắt hơn nhiều so với việc đánh giá State Machine đơn giản (~0.008 ms), nhưng tổng chi phí worker thread cho toàn bộ pipeline animation (bao gồm cả blending, procedural IK) thường ở mức tương đương (~0.4 – 0.6 ms) vì Motion Matching giảm bớt các node xử lý phức tạp khác.
- **Rủi ro kỹ thuật cho Eclipse:**
  - Chưa có benchmark thực tế trên CPU của máy dev (Intel Core i7-13620H) với phiên bản UE 5.8.
  - Mục tiêu hiệu năng ([05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md)): **Game thread $\le$ 6 ms**. Nếu spawn 5–10 AI Enemy đồng thời đều chạy Pose Search không kiểm soát, worker thread và game thread có thể bị nghẽn.
- **Biện pháp tối ưu đề xuất (dựa trên tài liệu Epic):**
  1. Phân vùng Database bằng **Chooser Table** (chỉ query database nhỏ tương ứng với Gait hiện tại).
  2. Bật **Animation Update Rate Optimization (URO)** để giảm tần suất tick animation của enemy ở xa.
  3. Sử dụng Database LOD hoặc chuyển AI quái thường sang State Machine truyền thống / Inertialization.
- **Hành động kiểm chứng (Tier A / Con người):** Dùng công cụ **Unreal Insights** (kênh `Cpu`, `Animation`, `PoseSearch`) trực tiếp trên máy dev khi triển khai 1 Player và 3–5 Enemy để đo đạc thông số thực tế trước khi chốt kiến trúc locomotion cho AI.
- **Nguồn xác minh:**
  - [Epic Docs: Animation Debugging and Optimization in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/animation-debugging-and-optimization-in-unreal-engine)
  - [Epic Games Presentation: Motion Matching in Unreal Engine 5 (Unreal Fest)](https://dev.epicgames.com/community/learning)

---

## 8. Khuyến nghị cho Eclipse (≤ 10 dòng)
1. **Dùng GASP cho Player Locomotion:** Hướng đi đúng (ADR-007), miễn phí bản quyền thương mại theo Fab Standard License.
2. **Kiểm tra Skeleton trong Editor:** Mở `UEFN_Mannequin` kiểm tra; ưu tiên dùng IK Retargeter `RTG_UEFN_to_UE5` có sẵn để xuất animation sang `SK_Mannequin` chuẩn của Eclipse thay vì ép dùng chung asset.
3. **Không tải trực tiếp vào repo:** Tải GASP về thư mục tạm/ổ ngoài để bảo vệ dung lượng SSD ~113 GB còn lại (ADR-009).
4. **Chỉ migrate locomotion cốt lõi:** Chỉ lấy `ABP_SandboxCharacter`, Chooser Table và database locomotion; không migrate Mover hay Traversal.
5. **Chỉ bật 7 plugin cốt lõi:** Bật 7 plugin nhóm 4A trong `Eclipse.uproject`.
6. **Benchmark hiệu năng bằng Unreal Insights:** Không áp dụng Motion Matching cho quái thường nếu chưa profile thực tế trên máy dev; dự phòng dùng State Machine + URO cho Enemy.
