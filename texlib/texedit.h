/* Copyright (C) 2015 Dr. Michael Robb

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General License
   as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   The program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Public License for more details.

   You should have received a copy of the GNU Public License 
   along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
// ==========================================================================
// Texture editing
// ==========================================================================
#ifndef _TEXTURE_EDIT_H_
#define _TEXTURE_EDIT_H_

class CTextureEdit : virtual public CTexture
{
public:
// ===== Editing ============================================================

// ----- Texture quantization -----------------------------------------------

void         TextureQuantize( int ncolors );
colmap4f *TextureQuantizePalette( int ncolors );
void         TexturePreQuantize( void );

// ----- Color element access routines --------------------------------------

void TextureClear( float red, float green, float blue, float alpha );

void TextureClearRange( int xlo, int ylo, int xhi, int yhi,
                        float red, float green, float blue, float alpha );

inline void TextureClear( col4f &pixel )
        {
        TextureClear( pixel.m_red, pixel.m_green, pixel.m_blue, pixel.m_alpha );
        }

inline void TextureClearRange( int xlo, int ylo, int xhi, int yhi, col4f &pixel )
        {
        TextureClearRange( xlo, ylo, xhi, yhi,
                pixel.m_red, pixel.m_green, pixel.m_blue, pixel.m_alpha );
        }

void TextureCopyChannel( CTexture &texsrc, int chansrc, int chandst );

void TextureBiasChannel( int channel, float fbias );
void TextureScaleChannel( int channel, float fscale );

void TextureCalculateHistogram( float flow, float fhigh,
                  int *phistogram, int nsize, int reset );

// ----- Data format conversion routines ------------------------------------

void TextureChangeMode( int mode );
void TextureAlphaRemove( void );
void TextureAlphaInsert( void );
void TextureAlphaSet( float value );
void TextureExpand8to16bit( void );
void TextureReduce16to8bit( void );
void TextureExpand8bitToFloat( void );
void TextureExpand16bitToFloat( void );
void TextureReduceFloatTo16bit( void );
void TextureReduceFloatTo8bit( void );
void TextureMonoToRGB( void );
void TextureRGBToMono( void );
void TextureMonoToPalette( void );
void TexturePaletteToMono( void );
void TexturePaletteToRGB( void );

void TextureAlphaFromColour( float fr, float fg, float fb );

void TextureAlphaWater( void );

void TextureRGBToDual( void );
void TextureDualToRGB( void );
void TextureDualToMono( void );
void TextureMonoToDual( void );

// ----- Convolution --------------------------------------------------------

void TextureConvolve( col4f &cresult, CTexture &texconvolve,
                        int ix, int iy );

// -------------------------------------------------------------------------

void TextureConvertBayerToRGBFloat( void );

// ----- Post-processing ----------------------------------------------------

void TextureContrastNormalize( void );

void TextureProcess( int absolute, int normalize, int rgbflag,
                        int floatfloat, char *dstfile, int verbose );

// ----- Texture gamma correction -------------------------------------------

void TextureGammaCorrection( float gamma );
void TextureGammaCorrectionRamp( int *prampred, int *prampgreen, int *prampblue );

// ----- Texture cut and paste operations -----------------------------------

void TextureClipCoordinates( int &xlo, int &ylo, int &xhi, int &yhi );

void TextureCut(  CTexture &texdst, int xlo, int ylo, int xhi, int yhi );
void TexturePaste(             CTexture &texsrc, int xstart, int ystart );
void TexturePasteWraparound(   CTexture &texsrc, int xstart, int ystart );
int  TextureCheckWraparound( CTexture &texsrc, int xstart, int ystart, col3b &transp );

void InitialiseLimits( int wrap, int &xlo, int &ylo, int &xhi, int &yhi );

void TextureFindLimitsChannel( int channel, float &fmin, float &fmax );
void TextureFindLimits( col4f &clo, col4f &chi );

void TextureSwap( void );                       // TODO
void TextureSwap( CTexture &texsrc );           // TODO

void TextureDumpLimits( FILE *fp );             // TODO
void TextureDumpMemoryBounds( FILE *fp );       // TODO

// ----- Texture comparision functions --------------------------------------

float TextureCompare( CTexture &texdst, int chansrc, int chandst );

// ----- Texture colour manipulation routines -------------------------------

void TextureScale( float fred, float fgreen, float fblue, float falpha );

void TextureScale( col4f &cbias)
        {
        TextureScale( cbias.m_red, cbias.m_green, cbias.m_blue, cbias.m_alpha);
        }

void TextureScale8bit( float fred, float fgreen, float fblue );

void TextureBias(  float fred, float fgreen, float fblue, float falpha );

void TextureBias( col4f &cbias)
        {
        TextureBias( cbias.m_red, cbias.m_green, cbias.m_blue, cbias.m_alpha);
        }

void TextureMakeWaveEdges( float *fbase, float *fphase, float *famp, float *fwave, int num );

// ----- Texture arithmetic -------------------------------------------------

void TextureFindMaxDelta( float *pdelta );
void TextureFindMaxDeltaChannel( int channel, float &fdelta );

// ----- Texture arithmetic -------------------------------------------------

void TextureAdd(      CTexture &Texturesrca, CTexture &Texturesrcb );
void TextureAdd(      CTexture &Texturesrca );
void TextureSubtract( CTexture &Texturesrca, CTexture &Texturesrcb );
void TextureSubtract( CTexture &Texturesrca );
void TextureMultiply( CTexture &Texturesrca, CTexture &Texturesrcb );
void TextureMultiply( CTexture &Texturesrca );
void TextureDivide(   CTexture &Texturesrca, CTexture &Texturesrcb );
void TextureDivide(   CTexture &Texturesrca );
void TextureSqrt(     void );
void TextureSqrt(     CTexture &Texturesrca );
void TextureScale(    CTexture &Texturesrca, float scale );
void TextureInvert( float fvalue );
void TextureClampMinimum( float fmin );
void TextureClampMaximum( float fmax );
void TextureSumSquares( CTexture &texsrca, CTexture &texsrcb );

void TextureNormalise( float fvariance, float fmean );

void TextureConvertSignToBitone( void );
void  TextureCalculateSquare( void );
void  TextureCalculateAbsolute( void );
float TextureCalculateAverage( void );
float TextureCalculateAverageRange( int xlo, int xhi, int ylo, int yhi );

void  TextureScale( CTexture &scopesrc, int width, int height );
void  TextureTile(  CTexture &scopesrc, int width, int height );

void TextureStatisticsList( CTexture *pimagelist, int imagenum,
                float &fmax,    float &fmin, float &fmean, float &fvariance,
                float &fstddev, float &fsum, float &fsum2, float &ftotalpix );

void TextureScale( float fscale );

void TextureBias( float fbias );
void TextureBiasFlip( float fbias );

void TextureScaleRange( float flo, float fhi, int mode );

float TextureFindAverageChannel( int channel );
float TextureFindTotalChannel( int channel );

int   TextureCheckChannels( char *message );

// ----- Texture trigonometry -----------------------------------------------

void TextureSin(  void );
void TextureSin(  CTexture &texsrca );
void TextureCos(  void );
void TextureCos(  CTexture &texsrca );
void TextureTan(  void );
void TextureTan(  CTexture &texsrca );
void TextureAcos( void );
void TextureAcos( CTexture &texsrca );
void TextureAsin( void );
void TextureAsin( CTexture &texsrca );
void TextureAtan( void );
void TextureAtan( CTexture &texsrca );

void TextureAtan2( CTexture &texsrca, CTexture &texsrcb );

// ----- Texture warping ----------------------------------------------------

void TextureWarp( float fanglemax, CTexture &texsrc );

void TextureDizzy( int width, int height, int nu, int nv, float fphase );

void TextureMakeStarfishFilter( int width, int height,
                                float fmajor, float fminor, float freq,
                                float fphase, float fpower );
};

#endif	// _TEXTURE_EDIT_H_
