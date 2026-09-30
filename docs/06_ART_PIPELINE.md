# 06 — ART PIPELINE (Blender 4.5 → UE 5.8) + Image AI

> Không bắt đầu art thật trước M8 (sau Fun Gate). Trước đó chỉ greybox + asset tạm (Mannequin, pack miễn phí).

## 1. Thứ tự làm một asset
```
Concept (GPT Sol) → Blockout (Blender/Unreal) → TEST GAMEPLAY → High poly → Retopo → UV → Bake → Texture → (Rig/Skin) → Export → Import
```
Trạng thái asset: `BLOCKOUT → WIP → GAME_READY → POLISH → FINAL` — ghi trong tên thư mục hoặc metadata tag, không ghi trong tên file.

## 2. Blender
- Scene unit: **Metric, Unit Scale 0.01, Length Centimeters** (chốt). Mô hình nhân vật cao ~180 unit.
- File: `Hero_Master.blend` (+ `_High`, `_Rig`, `_Anim` khi cần). Không `final_REAL_FIX`. Version bằng git/backup, không bằng tên file.
- Collections: `COL_REF`, `COL_HIGH`, `COL_GAME`, `COL_RIG`, `COL_EXPORT`. **Chỉ `COL_EXPORT` được export.**
- Apply transform trước export (scale = 1, rotation = 0).
- Nhân vật người: skin vào hệ xương **tương thích UE5 Mannequin** (ADR-006). Kiểm tra bằng script (T-B, sau M7).

## 3. Export FBX
- Static mesh: FBX, Apply Transform, Forward -Y / Up Z (kiểm tra với một mesh chuẩn ở T-0xx và ghi lại), smoothing = Face, không export camera/light.
- Skeletal: chỉ Armature + Mesh, Add Leaf Bones = OFF, bake animation khi export anim.
- Script tự động: `Tools/Blender/export_col_export.py` (task Tier B ở M8).

## 4. Unreal import
- Nanite cho static mesh môi trường. Collision: tạo `UCX_` trong Blender cho mesh quan trọng, còn lại dùng auto convex.
- Material: dùng Master Material (`M_Master_Surface`, `M_Master_Character`), chỉ tạo Material Instance.
- Texture ORM (R=AO, G=Roughness, B=Metallic), sRGB off cho ORM/Normal.

## 5. Dùng GPT 6.1 Sol (Tier I) cho ảnh
Ảnh AI dùng làm **concept và tham chiếu**, không dùng trực tiếp làm texture cuối trừ icon/UI.

| Việc | Output | Dùng để |
|---|---|---|
| Mood board | 4–6 ảnh / khu vực | Thống nhất art direction |
| Character/Enemy/Boss concept | front view + 3/4 view | Thiết kế silhouette |
| **Orthographic reference sheet** | front + side + back, nền trơn, cùng tỉ lệ | Đặt làm background trong Blender để model |
| Prop/weapon sheet | nhiều góc | Model vũ khí |
| Icon item/UI | 512×512 nền trong suốt | Dùng trực tiếp trong UI |
| Texture tham khảo | tile ảnh | Tham khảo khi làm material (texture thật: tự làm/Megascans/Fab) |

Mẫu prompt (giữ cố định phần style để đồng bộ):
```
[STYLE] dark medieval fantasy, soulslike, grounded realistic proportions, muted desaturated palette,
weathered materials, painterly concept art, neutral grey background.
[SUBJECT] <mô tả>
[VIEW] orthographic front view and side view, full body, same scale, T-pose / A-pose, no perspective distortion.
[CONSTRAINTS] clear readable silhouette from distance, practical armor that can be modeled for a game,
no text, no watermark.
```
Lưu ảnh vào `ArtSource/Concept/<Nhóm>/<Tên>_vNN.png` (ngoài repo) và ghi prompt kèm theo trong file `.txt` cùng tên.

## 6. Pack & asset ngoài
- Nguồn ưu tiên: GASP (animation), Fab free/mua, Megascans (qua Fab).
- Luôn kiểm tra license trước khi dùng cho game thương mại.
- Ghi mọi asset ngoài vào `docs/THIRD_PARTY.md` (tên, nguồn, license, đường dẫn trong Content).
