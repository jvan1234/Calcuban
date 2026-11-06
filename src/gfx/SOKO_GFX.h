#ifndef SOKO_GFX_appvar_include_file
#define SOKO_GFX_appvar_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define SOKO_GFX_appvar_size 1330
#define sizeof_global_palette 40
#define global_palette (SOKO_GFX_appvar[0])
#define sprites_palette_offset 0
#define player_width 16
#define player_height 16
#define SOKO_GFX_sprites_player_index 1
#define player ((gfx_sprite_t*)SOKO_GFX_appvar[1])
#define box_width 16
#define box_height 16
#define SOKO_GFX_sprites_box_index 2
#define box ((gfx_sprite_t*)SOKO_GFX_appvar[2])
#define tileset_palette_offset 0
#define tileset_tile_width 16
#define tileset_tile_height 16
#define tileset SOKO_GFX_appvar[3]
#define tileset_tiles_num 3
extern unsigned char *tileset_tiles_data[3];
#define tileset_tiles ((gfx_sprite_t**)tileset_tiles_data)
#define tileset_tile_0 ((gfx_sprite_t*)tileset_tiles_data[0])
#define tileset_tile_1 ((gfx_sprite_t*)tileset_tiles_data[1])
#define tileset_tile_2 ((gfx_sprite_t*)tileset_tiles_data[2])
#define SOKO_GFX_entries_num 4
extern unsigned char *SOKO_GFX_appvar[4];
unsigned char SOKO_GFX_init(void);

#ifdef __cplusplus
}
#endif

#endif
