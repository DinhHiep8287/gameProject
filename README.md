Đinh Tuấn Hiệp 22028287

* **Tên Game : STEEL KNIGHT**

* **Chủ đề** : RPG

* **Video Demo :** https://www.youtube.com/watch?v=fjfiUtDZAQo

* **Tên Game : STEEL KNIGHT**

* **Giới thiệu :** : Game sử dụng thư viện đồ họa, âm thanh và chữ SDL 2.0. Nhập vai thành kỵ sĩ, chiến đấu với quái vật để giành được nhiều điểm nhất có thể.
                        
                        Di Chuyển : A - W - S - D
                        Tấn Công : J

* **Code Preview** : 
    + Lớp Game xử lý vòng lặp chính của game trong main.
    
    ```
    int main(int argc, char* argv[]) {
        //Khởi tạo
        FrameRateController frameRateController(FPS);
        Game::GetInstance()->init();
        // GAMELOOP
        while (Game::GetInstance()->state != EXIT)
        {
            frameRateController.startFrame();
    
            Game::GetInstance()->event();
            Game::GetInstance()->update();
            Game::GetInstance()->render();
    
            frameRateController.endFrame();
            
        }
        // THOÁT //
        Game::GetInstance()->cleanSDL();
    
        return 0;
    }
    ```
    + Lớp AssetManager xử lý các tài nguyên của game bao gồm các texture, sound, music, font,...
    + Lớp FrameRateController xử lý giới hạn khung hình của game.
    + Lớp Engine chủ yếu xử lý thư viện SDL.
    + Lớp Animation sẽ xử lý các hoạt ảnh của Object.
    + Lớp Input chủ yếu xử lý các Input của người dùng.
    + Các lớp trong folder Physic bao gồm Vector2D, Body tạo nên các yếu tố vật lý trong game, constants.h bao gồm các constant sử dụng bao gồm các đường dẫn, giá trị vật lý,...
    + Các lớp bao gồm Level, Tile, Layer sẽ tạo ra các màn chơi.
    + Các nhân vật trong game như Knight, Monster --kt-> Character --kt-> Object, việc xử lý va chạm, vật lý sẽ được chủ yếu xử lý trong Character.
    + Lớp Camera xử lý việc render sao cho render di chuyển theo chuyển động của nhân vật.
* **Nguồn đồ họa** : 

  - Knight <player> : https://luizmelo.itch.io/hero-knight-2
    
    [![knight.png](https://i.postimg.cc/gjB3Rkkt/knight.png)](https://postimg.cc/64n7xKZC)  

  - Quái Vật : https://luizmelo.itch.io/monsters-creatures-fantasy
    [![monster.png](https://i.postimg.cc/j5Mf0dNq/monster.png)](https://postimg.cc/G8stvRq6)
  
  - Tile : https://free-game-assets.itch.io/free-swamp-2d-tileset-pixel-art
  [![object.png](https://i.postimg.cc/MHcvC0qt/object.png)](https://postimg.cc/N2csTHyr)
  
  - Background :https://ansimuz.itch.io/mountain-dusk-parallax-background
   **( Background động : khi nhân vật chuyển động background sẽ di chuyển theo, các layer sẽ có mức di chuyển khác nhau phụ thuộc vào độ gần xa )**
   [![background.png](https://i.postimg.cc/0rR2hLt2/background.png)](https://postimg.cc/H8zgyPDf)

  - GUI: https://prinbles.itch.io/legend-buttons
  - 
  [![Screenshot-2024-08-18-194208.png](https://i.postimg.cc/vTBMT5FJ/Screenshot-2024-08-18-194208.png)](https://postimg.cc/r0v7Y0pj)
* **Nguồn âm thanh** :
  - Music: https://tallbeard.itch.io/music-loop-bundle
  - Sound Effect: https://leohpaz.itch.io/minifantasy-dungeon-sfx-pack

* **Font** : 
    - OpenSans: https://fonts.google.com/specimen/Open+Sans
    - Arcade: https://www.1001fonts.com/arcadeclassic-font.html

* **Map được custom bằng Tiled** : https://www.mapeditor.org/
                 
    [![tiled.png](https://i.postimg.cc/Vs3qYvp5/tiled.png)](https://postimg.cc/t7NZkqXH)             
* **Những thứ cần update:**
    + ~~Nhân vật rơi xuống vực chết~~
    + ~~Sửa tầm tấn công~~
    + ~~Thêm hoạt ảnh khi nhận sát thương~~
    + ~~Thêm hoạt ảnh khi nhân vật chết~~
    + ~~Cho quái vật di chuyển~~
    + ~~Thêm Menu~~
    + ~~Thêm Thanh máu + Điểm~~
    + ~~Thêm âm thanh~~
    + ~~Thêm gameOver + Replay~~
