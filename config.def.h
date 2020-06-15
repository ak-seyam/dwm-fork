/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx           = 2;        /* border pixel of windows */
static const unsigned int snap               = 20;       /* snap pixel */
static const int showbar                     = 1;        /* 0 means no bar */
static const int topbar                      = 0;        /* 0 means bottom bar */
static const unsigned int gappx              = 15;        /* gaps between windows */
static const char *fonts[]                   = { "FontAwesome:size=11" };
static const char dmenufont[]                = "FontAwesome:size=11";
static const char col_gray1[]                = "#222222"; // bar background
static const char col_gray2[]                = "#110022"; // inactive border background
static const char col_gray3[]                = "#999999"; // unselected elements in bar
static const char col_gray4[]                = "#eeeeee"; // selected elements in bar
static const unsigned char barPadding       = 10  ; // selected elements in bar
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const char col_active[]        = "#0F2871";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_active,  col_active  },
	[SchemeNMaster]  = { "#ffffff", "#aa0000",  col_gray2  },
};


/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const char nmaster_icon[]="[]";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tagsMask     isfloating   monitor */
	{ "Gimp"         ,NULL  ,    NULL,       0,            1,           -1 },
	{ "Brave-browser",NULL  ,    NULL,       1 << 1,       0,           -1 },
	{ "Slimjet"      ,NULL  ,    NULL,       1 << 1,       0,           -1 },
	{ "Thunar"       ,NULL  ,    NULL,       1 << 2,       0,           -1 },
	{ "qpdfview"     ,NULL  ,    NULL,       1 << 3,       0,           -1 },
	{ "tm"           ,NULL  ,    NULL,       1 << 8,       0,           -1 },
	{ "isis.exe"     ,NULL  ,    NULL,       1 << 4,       0,           -1 },
	{ "Zathura"      ,NULL  ,    NULL,       1 << 3,       0,           -1 },
	{ "Spotify"      ,NULL  ,    NULL,       1 << 6,       0,           -1 },
	{ "vlc"          ,NULL  ,    NULL,       1 << 6,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const float smfact     = 0.00; /* factor of tiled clients [0.00..0.95] */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "[]",      NULL },    /* no layout function means floating behavior */
	{ "[]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define OPEN MODKEY
#define ENABLE MODKEY|ShiftMask
#define DISABLE MODKEY|ControlMask
#define BRWOSER "brave"
#define FILE_MANAGER "thunar"
#define SCREENSHOTTER "deepin-screen-recorder"
#define PROTEUS_ISIS "wine /run/media/a/myfiles/softwares/Proteus7.7/BIN/ISIS.EXE"

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#include"movestack.c"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_active, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { BRWOSER, NULL };
static const char *filemanager[]  = { "alacritty", "-e", "ranger" ,NULL};
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *screenshot[] = {SCREENSHOTTER, NULL};
static const char *playpause[] = {"playerctl","play-pause", NULL};



static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ OPEN  ,                       XK_Return, spawn,          {.v = termcmd } },
	{ OPEN  ,                       XK_w,      spawn,          {.v = browsercmd } },
	{ OPEN  ,                       XK_f,      spawn,          {.v = filemanager } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ 0,                       XF86XK_MonBrightnessUp,      simple_exec,      {.v= "~/scripts/bctrl inc" } },
	{ 0,                       XF86XK_MonBrightnessDown,      simple_exec,      {.v= "~/scripts/bctrl dec" } },
	{ 0,                       XF86XK_AudioPlay,      simple_exec,      {.v= "playerctl play-pause" } },
	{ 0,                       XF86XK_AudioPause,      simple_exec,      {.v= "playerctl play-pause"} },
	{ 0,                       XF86XK_AudioNext,      simple_exec,      {.v= "playerctl next" } },
	{ 0,                       XF86XK_AudioPrev,      simple_exec,      {.v= "playerctl previous" } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ ENABLE,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ ENABLE,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ DISABLE,             XK_t,      simple_exec,            {.v = "xinput --disable 10; xdotool key XF86AudioPlay" } },
	{ ENABLE,             XK_t,      simple_exec,            {.v = "xinput --enable 10" } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },	
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } }    ,
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } }    ,
	// TODO a bug may arise here
	{ MODKEY|ShiftMask,             XK_h,      setsmfact,      {.sf = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setsmfact,      {.sf = -0.05} },
	// Till here
	{ OPEN,                         XK_p,      simple_exec,    {.v = PROTEUS_ISIS } }    ,
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ 0,		                XK_Print,      spawn,           {.v = screenshot } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

