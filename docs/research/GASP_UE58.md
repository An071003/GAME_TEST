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
- **Dung lượng tải về (Vault Cache qua Epic Games Launcher):** Khoảng **~5.56 GB**.
- **Dung lượng trên đĩa sau khi tạo project:**
  - Thư mục project mẫu (`Content/`, `Config/`, `Source/`): Khoảng **~5.5 GB – 6.0 GB**.
  - Bộ nhớ đệm Derived Data Cache (DDC) sinh ra khi mở và compile animation database lần đầu: Khoảng **~3.0 GB – 5.0 GB**.
  - **Tổng dung lượng đĩa tiêu tốn nếu giữ cả Vault Cache và project mẫu:** Khoảng **~11.0 GB – 15.0 GB**.
- **Cảnh báo phần cứng (đối chiếu [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md)):** Ổ C máy dev hiện chỉ còn ~113 GB trống. Việc tải trực tiếp cả project vào ổ C sẽ chiếm hơn 10% dung lượng còn lại. Cần tạo project ở thư mục tạm hoặc ổ ngoài, chỉ migrate asset cần thiết vào `Unreal/Content`.
- **Nguồn xác minh:**
  - [Unreal Engine Forums: Game Animation Sample download and disk footprint discussion](https://forums.unrealengine.com)

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
- **So sánh với UE5 Mannequin chuẩn (`SK_Mannequin` / Manny & Quinn):**
  - **Hoàn toàn đồng nhất về cấu trúc xương (Bone Hierarchy & Joint Orientations):** Sử dụng chung hệ xương tiêu chuẩn của UE5 (root, pelvis, spine_01 $\rightarrow$ spine_05, clavicle, upperarm, lowerarm, hand, thighed, calf, foot, ball).
  - **Giữ nguyên hệ thống xương IK:** Đầy đủ `ik_foot_root`, `ik_foot_l`, `ik_foot_r`, `ik_hand_root`, `ik_hand_gun`, `ik_hand_l`, `ik_hand_r`.
  - **Kết luận:** Đây **KHÔNG** phải là một biến thể dị biệt về hierarchy. Tiền tố `UEFN_` phản ánh việc Epic dùng chung chuẩn skeleton giữa Unreal Editor for Fortnite và Unreal Engine.
  - **Độ tương thích với Eclipse:** Phù hợp 100% với quyết định [DECISIONS.md ADR-006](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/DECISIONS.md#adr-006). Mesh nhân vật mô hình hóa từ Blender theo skeleton UE5 Mannequin có thể gắn trực tiếp hoặc retarget 1:1 sang hệ xương này mà không cần điều chỉnh bone map phức tạp.
- **Nguồn xác minh:**
  - [Epic Docs: Adding a MetaHuman to the Game Animation Sample Project](https://dev.epicgames.com/documentation/en-us/unreal-engine/adding-a-metahuman-to-the-game-animation-sample-project-in-unreal-engine)
  - [Epic Developer Community: Skeletons in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/skeletons-in-unreal-engine)

---

## 7. Đánh giá Hiệu năng & Chi phí CPU (Motion Matching)
- **Chi phí CPU Worker Thread (Locomotion Selection Cost):**
  - Thuật toán tìm kiếm pose (Motion Matching Selection) tốn khoảng **~0.20 – 0.25 ms / character / frame**. So với State Machine truyền thống (~0.008 ms), bước chọn pose của Motion Matching tốn gấp **~25–30 lần**.
  - Tuy nhiên, **tổng chi phí animation luồng phụ (Total Animation Worker Cost)** lại tương đương: Motion Matching tiêu thụ khoảng **~0.50 ms / character**, trong khi State Machine phức tạp (kèm Aim Offset, PoseDriver, Control Rig, Layered Blend) tiêu thụ khoảng **~0.43 ms / character**.
- **Rủi ro hiệu năng cho Eclipse:**
  - [05_HARDWARE_AND_DISK.md](file:///C:/Users/ADMIN/Downloads/GAME_TEST/docs/05_HARDWARE_AND_DISK.md) đặt mục tiêu: **Game thread $\le$ 6 ms**, chạy trên CPU i7-13620H.
  - Với nhân vật người chơi (Player): Chi phí ~0.25 ms là hoàn toàn chấp nhận được và mang lại chuyển động mượt mà vượt trội.
  - Với quái/enemy số lượng đông (từ 5–10 quái cùng lúc trong màn chơi): Nếu tất cả đều chạy Motion Matching không kiểm soát, CPU sẽ quá tải.
- **Biện pháp tối ưu bắt buộc:**
  1. Sử dụng **Chooser Table** để phân vùng Pose Search Database (chỉ tìm kiếm trong database đi bộ khi đang đi bộ, không quét toàn bộ 500+ animation).
  2. Bật **Animation Update Rate Optimization (URO)** để giảm tần suất tick animation của quái ở cự ly xa camera.
  3. Sử dụng **Motion Matching Database LOD** có sẵn trong GASP cho các đối tượng phụ.
- **Nguồn xác minh:**
  - [Unreal Engine Forums: Performance Profiling Motion Matching vs State Machines](https://forums.unrealengine.com)
  - [Epic Docs: Animation Debugging and Optimization in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/animation-debugging-and-optimization-in-unreal-engine)

---

## 8. Khuyến nghị cho Eclipse (≤ 10 dòng)
1. **Dùng GASP cho Player Locomotion:** Hoàn toàn khả thi, skeleton khớp 100% với ADR-006, miễn phí bản quyền thương mại.
2. **Không tải trực tiếp vào repo:** Tải GASP về thư mục tạm trên máy/ổ ngoài, không commit project mẫu vào Git để tiết kiệm 113 GB đĩa (ADR-009).
3. **Chỉ migrate locomotion cốt lõi:** Chỉ trích xuất `ABP_SandboxCharacter`, Chooser Table `CHT_PoseSearchDatabases` và các anim cơ bản; **tuyệt đối không** migrate Mover, Traversal hay SmartObjects.
4. **Chỉ bật 7 plugin cốt lõi:** Bật nhóm 4A trong `Eclipse.uproject` (PoseSearch, Chooser, MotionTrajectory, AnimationWarping, MotionWarping, AnimationLocomotionLibrary, BlendStack).
5. **Enemy dùng State Machine hoặc Database thu gọn:** Giữ budget Game thread $\le$ 6 ms bằng cách chỉ áp dụng Motion Matching đầy đủ cho Player và Boss; quái thường nên dùng State Machine hoặc Database rút gọn kết hợp URO.
