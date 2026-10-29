#ifndef tileset_include_file
#define tileset_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define tileset_tile_0 ((gfx_sprite_t*)tileset_tile_0_data)
extern unsigned char tileset_tile_0_data[258];
#define tileset_tile_1 ((gfx_sprite_t*)tileset_tile_1_data)
extern unsigned char tileset_tile_1_data[258];
#define tileset_tile_2 ((gfx_sprite_t*)tileset_tile_2_data)
extern unsigned char tileset_tile_2_data[258];
#define tileset_num_tiles 3
#define tileset_tiles ((gfx_sprite_t**)tileset_tiles_data)
extern unsigned char *tileset_tiles_data[3];

#ifdef __cplusplus
}
#endif

#endif
