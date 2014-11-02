/*
PROGMEM is a way to store the array in the flash of the device.
The size of the array has no impact on avaliable RAM memory since
the needed entry is fetched at runtime

This incurs minimal performance of 3 clock cycles for recall instead of 2

TODO: Tomasz - Add a new entry in every second place in order to provide finer control
      then just make speed advance by 2 instead of 1 now that space is no issue.
*/

PROGMEM  prog_uint16_t accel_table[] =  {
    
    // TODO: Tomasz - What does this mean?
    4633, // NOTE: We can't have zero as compare register:
    7749, 3210, 2463, 2076, 1829, 1654, 1521, 1416, 1330, 1257,
    1196, 1143, 1096, 1055, 1018,  984,  954,  926,  901,  877,
     856,  836,  817,  799,  783,  767,  753,  739,  726,  713,
     702,  690,  680,  669,  660,  650,  641,  633,  624,  616,
     609,  601,  594,  587,  581,  574,  568,  562,  556,  551,
     545,  540,  535,  530,  525,  520,  515,  511,  507,  502,
     498,  494,  490,  486,  482,  479,  475,  472,  468,  465,
     461,  458,  455,  452,  449,  446,  443,  440,  437,  435,
     432,  429,  427,  424,  421,  419,  417,  414,  412,  410,
     407,  405,  403,  401,  399,  396,  394,  392,  390,  388,
     386,  385,  383,  381,  379,  377,  375,  374,  372,  370,
     369,  367,  365,  364,  362,  361,  359,  357,  356,  354,
     353,  351,  350,  349,  347,  346,  344,  343,  342,  340,
     339,  338,  337,  335,  334,  333,  332,  330,  329,  328,
     327,  326,  325,  323,  322,  321,  320,  319,  318,  317,
     316,  315,  314,  313,  312,  311,  310,  309,  308,  307,
     306,  305,  304,  303,  302,  301,  300,  299,  298,  298,
     297,  296,  295,  294,  293,  292,  292,  291,  290,  289,
     288,  288,  287,  286,  285,  284,  284,  283,  282,  281,
     281,  280,  279,  279,  278,  277,  276,  276,  275,  274,
     274,  273,  272,  272,  271,  270,  270,  269,  268,  268,
     267,  266,  266,  265,  265,  264,  263,  263,  262,  262,
     261,  260,  260,  259,  259,  258,  257,  257,  256,  256,
     255,  255,  254,  254,  253,  252,  252,  251,  251,  250,
     250,  249,  249,  248,  248,  247,  247,  246,  246,  245,
     245,  244,  244,  243,  243,  242,  242,  241,  241,  241,
     240,  240,  239,  239,  238,  238,  237,  237,  236,  236,
     236,  235,  235,  234,  234,  233,  233,  233,  232,  232,
     231,  231,  231,  230,  230,  229,  229,  229,  228,  228,
     227,  227,  227,  226,  226,  225,  225,  225,  224,  224,
     224,  223,  223,  222,  222,  222,  221,  221,  221,  220,
     220,  220,  219,  219,  218,  218,  218,  217,  217,  217,
     216,  216,  216,  215,  215,  215,  214,  214,  214,  213,
     213,  213,  212,  212,  212,  212,  211,  211,  211,  210,
     210,  210,  209,  209,  209,  208,  208,  208,  208,  207,
     207,  207,  206,  206,  206,  205,  205,  205,  205,  204,
     204,  204,  203,  203,  203,  203,  202,  202,  202,  202,
     201,  201,  201,  200,  200,  200,  200,  199,  199,  199,
     199,  198,  198,  198,  198,  197,  197,  197,  197,  196,
     196,  196,  196,  195,  195,  195,  195,  194,  194,  194,
     194,  193,  193,  193,  193,  192,  192,  192,  192,  191,
     191,  191,  191,  191,  190,  190,  190,  190,  189,  189,
     189,  189,  188,  188,  188,  188,  188,  187,  187,  187,
     187,  187,  186,  186,  186,  186,  185,  185,  185,  185,
     185,  184,  184,  184,  184,  184,  183,  183,  183,  183,
     183,  182,  182,  182,  182,  182,  181,  181,  181,  181,
     181,  180,  180,  180,  180,  180,  179,  179,  179,  179,
     179,  178,  178,  178,  178,  178,  177,  177,  177,  177,
     177,  177,  176,  176,  176,  176,  176,  175,  175,  175,
     175,  175,  175,  174,  174,  174,  174,  174,  174,  173,
     173,  173,  173,  173,  172,  172,  172,  172,  172,  172,
     171,  171
};
