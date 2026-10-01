# T-014 — Script Python Editor tạo `IA_*` + `IMC_Gameplay`

| | |
|---|---|
| Status | TODO (chờ bước 0 của Lead) |
| Milestone | M1 |
| Tier | B (viết script) · A (bước 0, review) · Human (chạy script trong Editor) |
| Gợi ý model | GPT Luna 6 |
| Phụ thuộc | T-003; bước 0 do Lead làm |
| Branch | `task/T-014-input-assets` |

## Mục tiêu
Chạy **một** script trong Editor → tạo/cập nhật 11 Input Action + 1 Input Mapping Context đúng bảng dưới. Chạy lại lần 2 không tạo trùng, không lỗi.

## Đọc trước
- `AGENTS.md` (nhất là luật 7: không bịa API), `docs/03_CONVENTIONS.md` §1, §2

## Bước 0 — Lead (Claude) làm trước, KHÔNG phải Tier B
- Bật plugin `PythonScriptPlugin` (Beta) và `EditorScriptingUtilities` (Beta) trong `Unreal/Eclipse.uproject` (đã xác minh tồn tại trong `UE_5.8/Engine/Plugins`).
- Human: mở Editor → Editor Preferences → Plugins - Python → bật **Developer Mode** → khởi động lại Editor. Việc này sinh file stub API `Unreal/Intermediate/PythonStub/unreal.py`.

## Được phép sửa / tạo (Tier B)
- `Tools/Python/create_input_assets.py` (tạo mới)
- Task card này (Handoff)

## Cấm
- Không sửa `.uproject`, `.ini`, C++, không tự tạo `.uasset` (chỉ con người chạy script trong Editor).

## Bảng Input (giá trị khởi đầu — con người đổi phím thoải mái trong Editor sau này)
Thư mục: IA → `/Game/Eclipse/Input/Actions`, IMC → `/Game/Eclipse/Input/Contexts/IMC_Gameplay`.

| Asset | Value Type | Bàn phím/chuột | Gamepad |
|---|---|---|---|
| `IA_Move` | Axis2D | `W`, `A`, `S`, `D` | `Gamepad_Left2D` |
| `IA_Look` | Axis2D | `Mouse2D` | `Gamepad_Right2D` |
| `IA_LightAttack` | Boolean | `LeftMouseButton` | `Gamepad_RightShoulder` |
| `IA_HeavyAttack` | Boolean | `F` | `Gamepad_RightTrigger` |
| `IA_Block` | Boolean | `RightMouseButton` | `Gamepad_LeftShoulder` |
| `IA_Parry` | Boolean | `LeftAlt` | `Gamepad_LeftTrigger` |
| `IA_Dodge` | Boolean | `SpaceBar` | `Gamepad_FaceButton_Right` |
| `IA_Sprint` | Boolean | `LeftShift` | `Gamepad_FaceButton_Right` |
| `IA_LockOn` | Boolean | `MiddleMouseButton`, `Q` | `Gamepad_RightThumbstick` |
| `IA_UseItem` | Boolean | `R` | `Gamepad_FaceButton_Left` |
| `IA_Interact` | Boolean | `E` | `Gamepad_FaceButton_Bottom` |

Tên phím (cột 3–4) là tên `FKey` của Unreal — Claude đã xác minh cả 17 tên có trong `InputCoreTypes.h` của 5.8 (2026-10-01). Khi viết script vẫn đối chiếu với `EKeys` (tìm trong stub hoặc `Engine/Source/Runtime/InputCore/Classes/InputCoreTypes.h`). Tên nào không tìm thấy → ghi vào Blocker, không đoán.

## Các bước (Tier B)
1. Trước khi viết mỗi lệnh API, `grep` trong `Unreal/Intermediate/PythonStub/unreal.py` để xác nhận class/hàm/thuộc tính tồn tại. Ghi lại các API đã dùng + dòng tìm thấy vào Handoff. Các API dự kiến cần (đều phải xác minh):
   - `unreal.AssetToolsHelpers.get_asset_tools().create_asset(name, path, unreal.InputAction, None)`
   - `unreal.EditorAssetLibrary.does_asset_exist(path)`, `load_asset(path)`, `save_loaded_asset(asset)`
   - thuộc tính `value_type` của `unreal.InputAction`, enum `unreal.InputActionValueType`
   - `unreal.InputMappingContext.map_key(action, key)` / `unmap_all_keys...` (tên chính xác lấy từ stub)
   - `unreal.Key` và cách gán tên phím
2. Cấu trúc script:
   - Hằng số `ACTIONS = [...]` mô tả đúng bảng trên (tên, value type, list phím KBM, list phím gamepad). Không rải tên phím ở chỗ khác.
   - Hàm `get_or_create_action(name, value_type)`: tồn tại → load và cập nhật `value_type`; chưa có → tạo.
   - Hàm `get_or_create_imc()`; **xoá hết mapping cũ** của IMC (bằng API đã xác minh) rồi map lại theo bảng → chạy lần 2 không trùng.
   - Save mọi asset đã đổi. In `unreal.log(...)` tổng kết: số IA tạo mới / cập nhật, số mapping.
   - Bọc trong `def main():` + `if __name__ == "__main__": main()`.
3. **Không** thêm Modifier/Trigger bằng script (API instanced object dễ sai). Danh sách modifier/trigger cần thêm tay để ở mục "Việc Human" bên dưới.
4. Kiểm tra cú pháp: `python -m py_compile Tools/Python/create_input_assets.py` (Python của máy hoặc `UE_5.8/Engine/Binaries/ThirdParty/Python3/Win64/python.exe`).

## Việc Human (sau khi script chạy)
1. Editor → Tools → Execute Python Script… → chọn `Tools/Python/create_input_assets.py`. Output Log phải có dòng tổng kết, không có `Error`.
2. Chạy lại lần 2 → Content Browser không có asset trùng (`IA_Move_1`...).
3. Mở `IMC_Gameplay`, thêm tay:
   - `IA_Move`: `W` → Modifier **Swizzle Input Axis Values (YXZ)**; `S` → **Swizzle (YXZ)** + **Negate**; `A` → **Negate**; `D` → không.
   - `IA_Look`: `Mouse2D` → **Negate** chỉ trục Y (tuỳ cảm giác).
   - `IA_Dodge` mapping gamepad → Trigger **Tap**; `IA_Sprint` mapping gamepad → Trigger **Hold** (0.2 s). (Cùng nút B: chạm = lăn, giữ = chạy.)
4. Save All.

## Tiêu chí hoàn thành (kiểm tra được)
- [ ] `python -m py_compile` PASS.
- [ ] Handoff liệt kê mọi API Unreal đã dùng, mỗi cái kèm dòng tìm thấy trong stub.
- [ ] `grep -cE '"IA_[A-Za-z]+"' Tools/Python/create_input_assets.py` ≥ 11 và chỉ nằm trong hằng `ACTIONS`.
- [ ] Human: chạy 2 lần, có đúng 11 IA + 1 IMC, không trùng (Tier A xác nhận bằng cách liệt kê `Unreal/Content/Eclipse/Input`).

## Câu hỏi / Blocker
_(ghi vào đây nếu dừng)_

---
## Handoff (agent điền khi xong)
- File đã sửa/tạo:
- API đã dùng (kèm dòng trong stub):
- Chưa làm / CHƯA XÁC MINH:

## Review (Tier A điền)
- Kết luận:
