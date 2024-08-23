<?php

define("GED_SOURCE", "SOUR");
define("GED_SEX", "SEX");
define("GED_HUSBAND", "HUSB");
define("GED_WIFE", "WIFE");
define("GED_CHILD", "CHIL");
define("GED_TITLE", "TITL");
define("GED_ENGAGEMENT", "ENGA");
define("GED_MARRIAGE", "MARR");
define("GED_DIVORCE", "DIV");
define("GED_SEPARATION", "DIVF");
define("GED_NOTE", "NOTE");
define("GED_EDUCATION", "EDUC");
define("GED_OCCUPATION", "OCCU");
define("GED_BIRTH", "BIRT");
define("GED_DEATH", "DEAT");
define("GED_DATE", "DATE");
define("GED_PLACE", "PLAC");
define("GED_CONTINUED", "CONT");
define("GED_CONTINUED2", "CONC");
define("ANCESTRY_CATEGORY", "CATG");
define("HISTREG_ID", "HIST");

define("CONST_WORK_NOTE", "WORK");
define("MAX_DESC_LEVELS", 4);
define("VERTICAL", "vert");
define("HORIZONTAL", "hori");
define("NO_IMAGE", "noim");
define("MAX_IMAGE_HEIGHT", 100);

date_default_timezone_set('Europe/Paris');
$now = getdate();
define("THIS_YEAR", $now["year"]);
?>
