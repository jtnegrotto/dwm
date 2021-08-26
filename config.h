/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 4;        /* border pixel of windows */
static const unsigned int gappx          = 5;        /* gap size */
static const unsigned int snap           = 32;       /* snap pixel */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;        /* systray spacing */
static const int systraypinningfailfirst = 1;        /* if pinning fails, display systray on the first monitor, false: display systray on the last monitor */
static const int showsystray             = 1;        /* 0 means no systray */
static const char *fonts[]               = { "Iosevka:size=12", "JoyPixels:size=12" };
static const unsigned int baralpha       = 0xF7;
static const unsigned int borderalpha    = OPAQUE;
static const unsigned int alphas[][3]    = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};
/* solarized colorscheme */
#ifdef LIGHT
static const char normbordercolor[] = "#fdf6e3";
static const char normbgcolor[]     = "#fdf6e3";
static const char normfgcolor[]     = "#839496";
static const char selbordercolor[]  = "#586e75";
static const char selbgcolor[]      = "#586e75";
static const char selfgcolor[]      = "#fdf6e3";
#else
static const char normbordercolor[] = "#002b36";
static const char normbgcolor[]     = "#002b36";
static const char normfgcolor[]     = "#657b83";
static const char selbordercolor[]  = "#93a1a1";
static const char selbgcolor[]      = "#93a1a1";
static const char selfgcolor[]      = "#002b36";
#endif

static const char *colors[][3] = {
	/*               fg           bg           border         */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,                       XK_b,           togglebar,      {0} },
	{ MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_bracketright,incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft, incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,         view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,           killclient,     {0} },
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,       setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,       setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,       setgaps,        {.i =  0 } },
	TAGKEYS(                        XK_1,                           0)
	TAGKEYS(                        XK_2,                           1)
	TAGKEYS(                        XK_3,                           2)
	TAGKEYS(                        XK_4,                           3)
	TAGKEYS(                        XK_5,                           4)
	TAGKEYS(                        XK_6,                           5)
	TAGKEYS(                        XK_7,                           6)
	TAGKEYS(                        XK_8,                           7)
	TAGKEYS(                        XK_9,                           8)
	{ MODKEY|ShiftMask,             XK_e,           quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
	IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
	IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
	IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
	IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
	IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
	IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
	IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

