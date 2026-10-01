# Dungeon01 — Art direction v01

## Một câu tóm tắt
Pháo đài-ngục chìm vào vách núi lạnh, nặng nề và hoang phế; ánh lửa hổ phách dẫn người chơi qua bóng tối tới nơi nghỉ và Warden.

## Bảng màu
Mẫu lấy trực tiếp từ ảnh v01, theo tọa độ pixel sau cắt (gốc trên trái); gỉ và gỗ giữ độ bão hòa thấp.

| Hex | Vai trò | Mẫu ảnh (x, y) |
|---|---|---|
| `#595859` | Nền: đá xám | Approach (855, 689) |
| `#343331` | Nền: sắt tối | Hall (392, 338) |
| `#493120` | Nhấn vật liệu: gỉ | Shortcut (304, 372) |
| `#5E5750` | Nền: gỗ bạc mục | Shortcut (1004, 645) |
| `#313526` | Nhấn phụ: rêu | Approach (438, 834) |
| `#777E86` | Nền sáng: phản chiếu lạnh | BossArena (819, 640) |
| `#C98D4F` | Dẫn đường: ánh lửa hổ phách | RestPoint (1002, 582) |

## Vật liệu & kit modular
Đá khối lớn ẩm, sắt rèn gỉ, gỗ mục; rêu/nước đọng tập trung ở mép. Kit tên tạm: `SM_Dungeon_Wall_A`, `SM_Dungeon_Floor_A`, `SM_Dungeon_Arch_A`, `SM_Dungeon_Stair_A`, `SM_Dungeon_Column_A`, `SM_Dungeon_CellBars_A`, `SM_Dungeon_IronGate_A`, `SM_Dungeon_Railing_A`, `SM_Dungeon_Chain_A`, `SM_Dungeon_LiftPlatform_A`, `SM_Dungeon_Winch_A`, `SM_Dungeon_FireBasin_A`. Lặp mô-đun, dành chi tiết cho chu vi.

## Ánh sáng
Ánh trời xám qua khe cao tạo nền lạnh; đuốc và rest point cùng một sắc hổ phách. Rest point có một chậu lửa làm nguồn sáng ấm duy nhất. Giữ Lumen mặc định; ít đèn động, giới hạn vùng chiếu và texture môi trường tối đa 2K cho máy 6 GB VRAM. Hiệu năng cần đo trong Editor.

## Đọc được (readability)
Vòm, cầu thang và vệt sáng nối tuyến chính; ánh ấm đánh dấu cổng/shortcut/nơi nghỉ. Giữ sàn trống, tương phản sau silhouette enemy, rêu/xích/đổ nát ngoài vùng combat. Greybox kiểm tra hành lang ≥ 300 cm, cửa 220–300 cm, người ~180 cm và khoảng trống camera dưới trần. Arena rộng, vật cản sát chu vi; fog gate không che boss và ranh giới sàn.

## Danh sách 6 ảnh
Các ảnh 1664×936 (16:9), mỗi ảnh có prompt `.txt` cùng tên tại cùng thư mục.

- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_Approach_v01.png` — Pháo đài trong vách núi, lối vào từ xa.
- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_Hall_v01.png` — Sảnh giam nhiều tầng, vòm và cầu thang nối tuyến.
- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_Corridor_v01.png` — Hành lang combat rộng, Hollow xa làm mốc tỉ lệ.
- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_Shortcut_v01.png` — Thang máy xích nối hai tầng, cơ cấu nhìn rõ.
- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_RestPoint_v01.png` — Chậu lửa trong phòng tối, sàn nghỉ thoáng.
- `G:\My Drive\Eclipse\ArtSource\Concept\Dungeon01\Dungeon01_BossArena_v01.png` — Warden sau fog gate, sàn đấu rộng và trống.
