# Báo cáo Nghiên cứu: Game Animation Sample (GASP) cho Unreal Engine 5.8

> **Mã task:** T-005 | **Milestone:** M0 | **Dự án:** Eclipse (UE 5.8)  
> **Mục đích:** Đánh giá tính khả thi, yêu cầu kỹ thuật và phương án tích hợp locomotion Motion Matching từ Game Animation Sample vào dự án Eclipse.

> ⚠ **Đã review (2026-10-01):** xem mục "Review" trong `docs/tasks/T-005-gasp-research.md` — các đính chính ở đó có hiệu lực cao hơn nội dung bên dưới (plugin §4, trajectory §5, skeleton §6).

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

---

## 9. Kiểm chứng T-008 (Claude, 2026-10-01) — đọc trực tiếp project `C:\UE_Temp\GASP58\GameAnimationSample`
Phương pháp: đọc `.uproject`, `Config/*.ini`, liệt kê `Content/`, quét name table của `.uasset` (`strings`/`grep`). **Chưa mở Editor để kiểm tra bind pose/bone** → các điểm đánh dấu *CHƯA XÁC MINH* cần làm ở T-015. Nếu mục này mâu thuẫn với §1–§8 thì **mục này đúng**.

### 9.1 Dung lượng (đo thật)
| Mục | Giá trị |
|---|---|
| Project `GameAnimationSample` | **7.2 GB** (`Content` ≈ 6.0 GB) |
| `Content/Characters` | 4.9 GB — Echo 1.1, **UEFN_Mannequin 2.7**, Paragon 0.75, UE5_Mannequins 0.35, UE4_Mannequin 0.02 |
| `Content/MetaHumans` / `IsolatedExamples` / `Movies` / `Levels` / `Blueprints` / `Audio` | 301 / 142 / 55 / 40 / 37 / 29 MB |
| `DerivedDataCache` trong project | 1.6 GB |
| Zen local cache toàn máy (`%LOCALAPPDATA%\UnrealEngine\Common\Zen\Data`) | 1.3 GB (đường dẫn **đã xác minh**, dùng cho T-004) |
| Ổ C: trống | 148 GB → **132 GB** sau khi tải + mở project (≈ −16 GB, gồm cả bản tải trong vault) |

Trong `UEFN_Mannequin/Animations` (2.7 GB): Crouch 722 MB, Walk 718, Run 536, Jump 188, Traversal 119, Interactions 109, Sprint 82, Slide 79, Idle 67, còn lại < 50 MB mỗi mục. `MotionMatchingData` chỉ 2.4 MB (data nhỏ, nặng ở animation). Soulslike cần trước: Idle + Walk + Run + Sprint + Jump ≈ **1.6 GB**; Crouch/Traversal/Interactions/Slide bỏ.

### 9.2 Plugin thật
- `.uproject` GASP bật 21 plugin (AnimationWarping, RigLogic, LiveLink, LiveLinkControlRig, PoseSearch, AnimationLocomotionLibrary, MotionWarping, HairStrands, Chooser, Mover, NetworkPrediction, ChaosMover, AnimationLayering, MoverExamples, MovieSceneAnimMixer, DrawDebugLibrary, SmartObjects, Locomotor, CurveExpression, GameplayInteractions + ModelingToolsEditorMode).
- **Không có `MotionTrajectory`** → GASP không dùng `CharacterTrajectoryComponent`. `BlendStack` không nằm trong `.uproject` (là dependency của PoseSearch).
- Name table của `SandboxCharacter_CMC_ABP` chỉ tham chiếu `PoseSearch`, `BlendStack`, `Chooser`-liên quan, `AnimGraphRuntime`. **Không** tham chiếu `AnimationLocomotionLibrary`, `Mover`, `SmartObjects`, `MotionTrajectory` (0 file trong `Blueprints/`, `Rigs/`, `MotionMatchingData/` chứa `/Script/AnimationLocomotionLibrary`).
- **Kết luận plugin cho Eclipse:** đã bật đủ ở T-003 (`PoseSearch`, `Chooser`, `MotionWarping`, `AnimationWarping`; BlendStack tự theo). **Không cần bật thêm plugin nào** để dùng ABP. `SandboxCharacter_CMC` (character BP) tham chiếu `SmartObjectAnimation`, `GameplayCameras` → **không migrate character BP**, chỉ migrate ABP (xem 9.4).

### 9.3 Trajectory
ABP gọi `PoseSearchGenerateTransformTrajectory` / `PoseSearchTrajectoryLibrary` / `GenerateTrajectory` (đều trong **PoseSearch**) + `PoseSearchHistoryCollector`. Đính chính §5 bước 6: **không thêm `CharacterTrajectoryComponent`**.

### 9.4 Cấu trúc asset thật (đính chính tên ở §5)
- Character có **hai biến thể**: `Blueprints/SandboxCharacter_CMC` (+ `SandboxCharacter_CMC_ABP`, dùng `CharacterMovementComponent`) và `SandboxCharacter_Mover` (+ `_Mover_ABP`, dùng Mover). **Eclipse dùng biến thể CMC.** Tên `ABP_SandboxCharacter`/`CBP_Sandbox_Character` trong §5 **không tồn tại** ở project này.
- ABP giao tiếp với character qua interface `BPI_SandboxCharacter_ABP` / `BPI_SandboxCharacter_Pawn`, enum `E_Gait`, `E_Stance`, `E_MovementMode`, `E_RotationMode`... (`Blueprints/Data/`). Eclipse C++ character phải cấp đúng các dữ liệu này cho ABP → việc của T-015.
- MM data: `Characters/UEFN_Mannequin/Animations/MotionMatchingData/` gồm 6 Chooser Table `CHT_PoseSearchDatabases{,_Dense,_ExtremeSparse,_Mover,_Relaxed,_Sparse}`, thư mục `Databases/{Dense,Sparse,Extreme_Sparse,Relaxed}`, 21 Schema `PSS_*`, 4 Normalization Set `PSN_*`. Bản CMC dùng `CHT_PoseSearchDatabases` (không hậu tố) — *CHƯA XÁC MINH trong ABP, Migrate dialog sẽ cho thấy*.
- Retarget: `Blueprints/RetargetedCharacters/ABP_GenericRetarget` + `BP_Manny`, `BP_Quinn`, `BP_Echo`, `BP_Twinblast`, `BP_UE4_Mannequin`. Retargeter có sẵn: **`RTG_UEFN_to_UE5_Mannequin`**, `RTG_UEFN_to_UE4_Mannequin`, `RTG_UEFN_to_Echo`, `RTG_UEFN_to_TwinBlast`, `RTG_UEFN_to_Metahuman_*` (IK Rig tương ứng `IK_*_Retarget`). Gemini đoán `RTG_UEFN_to_UE5` ≈ đúng, tên đầy đủ có hậu tố `_Mannequin`.

### 9.5 Skeleton
- GASP gồm **cả** `UEFN_Mannequin` (`SK_UEFN_Mannequin`, `SKM_UEFN_Mannequin`) **và** UE5 Mannequin (`SK_Mannequin`, `SKM_Manny`, `SKM_Quinn`) — vậy UE5 Mannequin có sẵn trong project, bản `Simple` cũng có.
- Hai skeleton **khác nhau**: quét tên bone cho thấy UE5 Mannequin có thêm hàng chục xương corrective/twist (`calf_knee_*`, `clavicle_*_back/down/fwd/up`, `lowerarm_*_fwd/bck`, `foot_*_up/down`...), UEFN có thêm `props_root`, `attach`, `contact_l/r`, `poi`, `face__*_eye_*`. (Quét chuỗi thô, chưa so sánh cây bone trong Editor → *CHƯA XÁC MINH* mức độ chính xác.) Vì vậy GASP cần retarget để chạy trên Manny — đây là lý do Epic ship `RTG_UEFN_to_UE5_Mannequin`.
- Hệ quả cho **ADR-006**: xem đề xuất trong `DECISIONS.md`.

### 9.6 Hiệu năng đo thật (chủ dự án chụp `stat unit`, Editor PIE, 1 nhân vật, map mặc định, RTX 4050 Laptop)
Frame 16.67 ms (đang bị khoá 60 FPS) · **Game 7.97 ms** · Draw 4.41 · RHIT 2.57 · **GPU 8.47 ms** · Mem 8.15 GB · VRAM 3.34 / 5.03 GB · RenderRes 92.9 % · Draws 284 · Prims 241 K.
- Đây là project **chưa tối ưu**, Scalability mặc định `Maximum`, chạy trong Editor (Editor tick + viewport tốn thêm) nên **không phải** số của Eclipse; chỉ để biết thứ tự độ lớn.
- **Game thread 7.97 ms đã vượt ngân sách 6 ms** (doc 05 §6) chỉ với 1 nhân vật. Chưa rõ bao nhiêu là Motion Matching (không có Insights). Cần đo lại ở T-015 sau khi bỏ debug/Traversal/SmartObjects và ở `Scalability = High`, **ngoài Editor** (Standalone/`-game`).
- VRAM 3.3/5.0 GB chỉ cho 1 nhân vật + map trống → Eclipse phải dè dặt với texture nhân vật (Echo/Paragon/MetaHuman không nên migrate).

### 9.7 License
Chủ dự án chưa ghi lại trang license trên Fab (Fab trả 403 cho tool của tôi). **Việc còn lại:** mở trang listing, chép nguyên dòng license vào `docs/THIRD_PARTY.md` (T-006). Lưu ý: `Paragon/TwinBlast`, `Echo`, `MetaHumans/*` có thể kèm điều khoản riêng (CHƯA XÁC MINH — không đọc được trang license). Eclipse không cần chúng nên không migrate.

### 9.8 Khuyến nghị migrate (thay thế §5 và Khuyến nghị 4–5)
1. Đừng migrate character BP. Viết `AEclipseCharacterBase` (T-012) rồi Migrate **chỉ** `SandboxCharacter_CMC_ABP` và xem **danh sách dependency** trong dialog Migrate trước khi bấm OK (đây là cách xác minh các điểm *CHƯA XÁC MINH*).
2. Chỉ giữ animation Idle, Walk, Run, Sprint, Jump (≈ 1.6 GB). Nếu Chooser Table kéo cả thư mục khác thì tạo bản `CHT_` + `PSD_` rút gọn riêng (thao tác Editor, ghi vào hướng dẫn T-015).
3. Giữ GASP gốc ở `C:\UE_Temp\GASP58` tới khi T-015 xong, rồi xoá (giải phóng ~9 GB gồm cả DDC).
4. Không bật SmartObjects/Mover/GameplayInteractions (ADR-009) — ABP CMC không cần.
