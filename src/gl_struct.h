/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *
 *---------------------------------------------------------------------
 */

#ifndef _GL_STRUCT_H
#define _GL_STRUCT_H

#include <SDL_opengl.h>

extern int nodesVersion;

typedef enum {
  filter_nearest,
  filter_linear,
  filter_nearest_mipmap_nearest,
  filter_nearest_mipmap_linear,
  filter_linear_mipmap_nearest,
  filter_linear_mipmap_linear,

  filter_count
} filter_texture_mode_t;

typedef enum {
  skytype_none,
  skytype_standard,
  skytype_skydome,
  skytype_screen,

  skytype_count
} skytype_t;

#define MAX_GLGAMMA 32
typedef enum
{
  gl_lightmode_glboom,
  gl_lightmode_gzdoom,
  gl_lightmode_fogbased,

  gl_lightmode_last
} gl_lightmode_t;
extern int gl_drawskys;
extern int gl_stretchsky;
extern int gl_hardware_gamma;
extern gl_lightmode_t gl_lightmode;
extern const char *gl_lightmodes[];
extern int gl_light_ambient;
extern int useglgamma;
int gld_SetGammaRamp(int gamma);
void gld_CheckHardwareGamma(void);
void gld_FlushTextures(void);
void gld_ApplyGammaRamp(byte *buf, int pitch, int width, int height);
void M_ChangeLightMode(void);
void M_ChangeSky(void);

extern int gl_seamless;
extern int render_canusedetail;
void gld_InitVertexData();
void gld_CleanVertexData();
void gld_UpdateSplitData(sector_t *sector);

extern int gl_boom_colormaps;
extern int gl_boom_colormaps_default;

void gld_Init(int width, int height);
void gld_InitCommandLine(void);
void gld_InitTextureParams(void);

void gld_DrawNumPatch(int x, int y, int lump, int cm, enum patch_translation_e flags);

void gld_FillFlat(int lump, int x, int y, int width, int height, enum patch_translation_e flags);
#define gld_FillFlatName(flatname, x, y, width, height, flags) \
  gld_FillFlat(R_FlatNumForName(flatname), (x), (y), (width), (height), (flags))

void gld_FillPatch(int lump, int x, int y, int width, int height, enum patch_translation_e flags);
#define gld_FillPatchName(name, x, y, width, height, flags) \
  gld_FillPatch(W_GetNumForName(name), (x), (y), (width), (height), (flags))

void gld_DrawLine(int x0, int y0, int x1, int y1, int BaseColor);
void gld_DrawWeapon(int weaponlump, vissprite_t *vis, int lightlevel);
void gld_FillBlock(int x, int y, int width, int height, int col);
void gld_SetPalette(int palette);
unsigned char *gld_ReadScreen(void);

void gld_CleanMemory(void);
void gld_PreprocessLevel(void);

void gld_Set2DMode();
void gld_InitDrawScene(void);
void gld_StartDrawScene(void);
void gld_AddPlane(int subsectornum, visplane_t *floor, visplane_t *ceiling);
void gld_AddWall(seg_t *seg);
void gld_AddSprite(vissprite_t *vspr);
void gld_DrawScene(player_t *player);
void gld_EndDrawScene(void);
void gld_Finish();

//stuff
extern int gl_color_mip_levels;

// wipe
int gld_wipe_doMelt(int ticks, int *y_lookup);
int gld_wipe_exitMelt(int ticks);
int gld_wipe_StartScreen(void);
int gld_wipe_EndScreen(void);

// hires
extern int gl_hires_24bit_colormap;
extern int gl_texture_external_hires;
extern int gl_texture_internal_hires;
extern int gl_hires_override_pwads;
extern char *gl_texture_hires_dir;
int gld_PrecacheGUIPatches(void);

//HQ resize
typedef enum
{
  hq_scale_none,
  hq_scale_2x,
  hq_scale_3x,
  hq_scale_4x,
  
  hq_scale_max
} gl_hqresizemode_t;
extern const char *gl_hqresizemodes[];
extern int gl_texture_hqresize;
extern int gl_texture_hqresize_textures;
extern int gl_texture_hqresize_sprites;
extern int gl_texture_hqresize_patches;

//clipper
dboolean gld_clipper_SafeCheckRange(angle_t startAngle, angle_t endAngle);
void gld_clipper_SafeAddClipRange(angle_t startangle, angle_t endangle);
void gld_clipper_Clear(void);
angle_t gld_FrustumAngle(void);

//missing flats (fake floors and ceilings)
extern dboolean gl_use_stencil;
sector_t* GetBestFake(sector_t *sector, int ceiling, int validcount);

//vertical sync for GL
extern int gl_vsync;

//shadows
typedef struct shadow_params_s
{
  int enable;
  int loaded;

  GLuint tex_id;
  int width;
  int height;

  int max_radius;
  int max_dist;
  float factor;
  float bias;
} simple_shadow_params_t;

extern simple_shadow_params_t simple_shadows;

void gld_DrawMapLines(void);
void gld_BeginLines(void);
void gld_EndLines(void);

#endif // _GL_STRUCT_H
