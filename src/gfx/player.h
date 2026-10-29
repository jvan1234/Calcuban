#ifndef player_include_file
#define player_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define player_width 16
#define player_height 16
#define player_size 258
#define player ((gfx_sprite_t*)player_data)
extern unsigned char player_data[258];

#ifdef __cplusplus
}
#endif

#endif
