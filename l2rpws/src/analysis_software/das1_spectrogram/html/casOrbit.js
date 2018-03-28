

// Constructor for the casOrbit Object
function casOrbit()
{
//"  A  2004-240T12:54 2004-326T08:23 ",
  this.Name="     ";
  this.tBeg="1997-180T00:00";
  this.tEnd="2020-001T00:00";

return;
}

function casOrbit_Lookup()
{
var sTmp;

  for(var i=0; i < casOrbit.arRaw.length; i++){
    if((this.tBeg >= casOrbit.arBeg[i]) && (this.tBeg <= casOrbit.arEnd[i]))
      this.Name="Orbit " + casOrbit.arName[i];
  }

return;
}



// Create and discard initial object instantce for the 
// prototype/inheritance voodoo to work (for Navigator 3.0)
new casOrbit();

// instance variables
//  Name,tBeg,tEnd

// instance methods
casOrbit.prototype.Lookup = casOrbit_Lookup;

// class variables
casOrbit.arName = new Array(40);
casOrbit.arBeg = new Array(50);
casOrbit.arEnd = new Array(60);
casOrbit.arRaw = new Array(
"0  2004-183T02:38 2004-240T12:54",
"A  2004-240T12:54 2004-326T08:23",
"B  2004-326T08:23 2004-366T07:03",
"C  2004-366T07:03 2005-032T03:27",
"3  2005-032T03:27 2005-058T06:21",
"4  2005-058T06:21 2005-078T17:36",
"5  2005-078T17:36 2005-096T23:33",
"6  2005-096T23:33 2005-113T23:31",
"7  2005-113T23:31 2005-132T03:57",
"8  2005-132T03:57 2005-150T08:25",
"9  2005-150T08:25 2005-168T13:15",
"10  2005-168T13:15 2005-186T19:00",
"11  2005-186T19:00 2005-205T01:46",
"12  2005-205T01:46 2005-223T08:13",
"13  2005-223T08:13 2005-240T11:46",
"14  2005-240T11:46 2005-257T16:00",
"15  2005-257T16:00 2005-275T23:07",
"16  2005-275T23:07 2005-294T00:05",
"17  2005-294T00:05 2005-317T05:05",
"18  2005-317T05:05 2005-345T04:20",
"19  2005-345T04:20 2006-005T14:07",
"20  2006-005T14:07 2006-036T20:57",
"21  2006-036T20:57 2006-068T03:34",
"22  2006-068T03:34 2006-099T10:19",
"23  2006-099T10:19 2006-130T16:30",
"24  2006-130T16:30 2006-161T23:06",
"25  2006-161T23:06 2006-193T05:17",
"26  2006-193T05:17 2006-216T21:24",
"27  2006-216T21:24 2006-240T19:12",
"28  2006-240T19:12 2006-260T17:06",
"29  2006-260T17:06 2006-276T18:53",
"30  2006-276T18:53 2006-292T22:09",
"31  2006-292T22:09 2006-307T00:09",
"32  2006-307T00:09 2006-318T23:34",
"33  2006-318T23:34 2006-330T22:23",
"34  2006-330T22:23 2006-342T21:07",
"35  2006-342T21:07 2006-356T23:27",
"36  2006-356T23:27 2007-008T04:37",
"37  2007-008T04:37 2007-024T12:27",
"38  2007-024T12:27 2007-041T10:51",
"39  2007-041T10:51 2007-058T07:48",
"40  2007-058T07:48 2007-074T12:41",
"41  2007-074T12:41 2007-090T17:09",
"42  2007-090T17:09 2007-106T20:52",
"43  2007-106T20:52 2007-122T23:33",
"44  2007-122T23:33 2007-139T01:11",
"45  2007-139T01:11 2007-155T01:20",
"46  2007-155T01:20 2007-171T01:17",
"47  2007-171T01:17 2007-190T09:52",
"48  2007-190T09:52 2007-221T16:31",
"49  2007-221T16:31 2007-257T11:46",
"50  2007-257T11:46 2007-285T10:13",
"51  2007-285T10:13 2007-309T08:14",
"52  2007-309T08:14 2007-329T08:00",
"53  2007-329T08:00 2007-345T05:33",
"54  2007-345T05:33 2007-361T01:25",
"55  2007-361T01:25 2008-009T22:30",
"56  2008-009T22:30 2008-021T21:13",
"57  2008-021T21:13 2008-033T20:02",
"58  2008-033T20:02 2008-045T19:28",
"59  2008-045T19:28 2008-056T22:08",
"60  2008-056T22:08 2008-067T13:02",
"61  2008-067T13:02 2008-078T04:39",
"62  2008-078T04:39 2008-088T01:29",
"63  2008-088T01:29 2008-097T15:25",
"64  2008-097T15:25 2008-107T05:07",
"65  2008-107T05:07 2008-116T18:23",
"66  2008-116T18:23 2008-126T07:36",
"67  2008-126T07:36 2008-135T00:10",
"68  2008-135T00:10 2008-142T23:22",
"69  2008-142T23:22 2008-150T09:02",
"70  2008-150T09:02 2008-157T11:47",
"71  2008-157T11:47 2008-164T14:30",
"72  2008-164T14:30 2008-171T17:03",
"73  2008-171T17:03 2008-178T19:36",
"74  2008-178T19:36 2008-185T22:03",
"75  2008-185T22:03 2008-192T23:20",
"76  2008-192T23:20 2008-199T23:27",
"77  2008-199T23:27 2008-206T23:40",
"78  2008-206T23:40 2008-213T19:50",
"79  2008-213T19:50 2008-221T05:07",
"80  2008-221T05:07 2008-228T14:08",
"81  2008-228T14:08 2008-235T22:42",
"82  2008-235T22:42 2008-243T07:40",
"83  2008-243T07:40 2008-250T16:33",
"84  2008-250T16:33 2008-258T01:24",
"85  2008-258T01:24 2008-265T10:14",
"86  2008-265T10:14 2008-272T19:03",
"87  2008-272T19:03 2008-280T03:35",
"88  2008-280T03:35 2008-287T11:41",
"89  2008-287T11:41 2008-294T19:07",
"90  2008-294T19:07 2008-302T02:15",
"91  2008-302T02:15 2008-309T23:29",
"92  2008-309T23:29 2008-317T22:29",
"93  2008-317T22:29 2008-325T10:17",
"94  2008-325T10:17 2008-333T09:31",
"95  2008-333T09:31 2008-340T18:21",
"96  2008-340T18:21 2008-348T17:48",
"97  2008-348T17:48 2008-356T13:04",
"98  2008-356T13:04 2008-366T00:11",
"99  2008-366T00:11 2009-009T13:58",
"100  2009-009T13:58 2009-019T03:43",
"101  2009-019T03:43 2009-028T17:09",
"102  2009-028T17:09 2009-039T02:36",
"103  2009-039T02:36 2009-051T01:22",
"104  2009-051T01:22 2009-063T00:20",
"105  2009-063T00:20 2009-074T23:18",
"106  2009-074T23:18 2009-086T04:51",
"107  2009-086T04:51 2009-094T01:29",
"108  2009-094T01:29 2009-106T23:05",
"109  2009-106T23:05 2009-122T01:37",
"110  2009-122T01:37 2009-137T13:44",
"111  2009-137T13:44 2009-153T00:44",
"112  2009-153T00:44 2009-168T14:08",
"113  2009-168T14:08 2009-184T05:04",
"114  2009-184T05:04 2009-199T21:28",
"115  2009-199T21:28 2009-215T15:23",
"116  2009-215T15:23 2009-231T11:08",
"117  2009-231T11:08 2009-251T10:15",
"118  2009-251T10:15 2009-275T08:03",
"119  2009-275T08:03 2009-296T16:59",
"120  2009-296T16:59 2009-315T16:57",
"121  2009-315T16:57 2009-334T17:36",
"122  2009-334T17:36 2009-352T05:54",
"123  2009-352T05:54 2010-003T03:49",
"124  2010-003T03:49 2010-019T04:17",
"125  2010-019T04:17 2010-035T22:18",
"126  2010-035T22:18 2010-053T11:27",
"127  2010-053T11:27 2010-071T01:42",
"128  2010-071T01:42 2010-088T17:01",
"129  2010-088T17:01 2010-107T17:20",
"130  2010-107T17:20 2010-128T03:04",
"131  2010-128T03:04 2010-146T08:04",
"132  2010-146T08:04 2010-162T07:27",
"133  2010-162T07:27 2010-178T05:23",
"134  2010-178T05:23 2010-196T04:21",
"135  2010-196T04:21 2010-216T02:12",
"136  2010-216T02:12 2010-236T01:18",
"137  2010-236T01:18 2010-256T00:44",
"138  2010-256T00:44 2010-277T21:02",
"139  2010-277T21:02 2010-301T18:21",
"140  2010-301T18:21 2010-324T01:56",
"141  2010-324T01:56 2010-344T16:15",
"142  2010-344T16:15 2010-365T07:30",
"143  2010-365T07:30 2011-020T21:28",
"144  2011-020T21:28 2011-041T08:05",
"145  2011-041T08:05 2011-065T12:39",
"146  2011-065T12:39 2011-093T10:51",
"147  2011-093T10:51 2011-119T03:06",
"148  2011-119T03:06 2011-150T10:15",
"149  2011-150T10:15 2011-180T19:56",
"150  2011-180T19:56 2011-202T12:10",
"151  2011-202T12:10 2011-224T06:01",
"152  2011-224T06:01 2011-246T01:47",
"153  2011-246T01:47 2011-265T19:58",
"154  2011-265T19:58 2011-283T14:40",
"155  2011-283T14:40 2011-301T10:10",
"156  2011-301T10:10 2011-319T06:12",
"157  2011-319T06:12 2011-337T03:13",
"158  2011-337T03:13 2011-357T19:14",
"159  2011-357T19:14 2012-016T15:46",
"160  2012-016T15:46 2012-040T12:16",
"161  2012-040T12:16 2012-061T03:51",
"162  2012-061T03:51 2012-078T23:54",
"163  2012-078T23:54 2012-096T19:17",
"164  2012-096T19:17 2012-114T14:46",
"165  2012-114T14:46 2012-132T09:28",
"166  2012-132T09:28 2012-149T05:15",
"167  2012-149T05:15 2012-169T01:46",
"168  2012-169T01:46 2012-192T23:45",
"169  2012-192T23:45 2012-215T10:52",
"170  2012-215T10:52 2012-236T16:38",
"171  2012-236T16:38 2012-257T23:17",
"172  2012-257T23:17 2012-280T10:18",
"173  2012-280T10:18 2012-304T08:16",
"174  2012-304T08:16 2012-324T02:54",
"175  2012-324T02:54 2012-338T10:58",
"176  2012-338T10:58 2012-351T17:22",
"177  2012-351T17:22 2012-364T23:50",
"178  2012-364T23:50 2013-012T06:43",
"179  2013-012T06:43 2013-025T13:55",
"180  2013-025T13:55 2013-038T21:11",
"181  2013-038T21:11 2013-051T05:02",
"182  2013-051T05:02 2013-063T04:01",
"183  2013-063T04:01 2013-075T03:13",
"184  2013-075T03:13 2013-087T02:16",
"185  2013-087T02:16 2013-097T17:49",
"186  2013-097T17:49 2013-107T07:25",
"187  2013-107T07:25 2013-116T21:08",
"188  2013-116T21:08 2013-126T10:48",
"189  2013-126T10:48 2013-136T00:29",
"190  2013-136T00:29 2013-146T07:37",
"191  2013-146T07:37 2013-158T06:29",
"192  2013-158T06:29 2013-170T05:34",
"193  2013-170T05:34 2013-182T04:38",
"194  2013-182T04:38 2013-196T06:14",
"195  2013-196T06:14 2013-217T16:37",
"196  2013-217T16:37 2013-241T14:48",
"197  2013-241T14:48 2013-270T15:02",
"198  2013-270T15:02 2013-311T06:31",
"199  2013-311T06:31 2013-351T21:24",
"200  2013-351T21:24 2014-019T10:10",
"201  2014-019T10:10 2014-051T16:45",
"202  2014-051T16:45 2014-083T18:01",
"203  2014-083T18:01 2014-117T13:47",
"204  2014-117T13:47 2014-151T08:36",
"205  2014-151T08:36 2014-183T06:52",
"206  2014-183T06:52 2014-215T06:56",
"207  2014-215T06:56 2014-247T01:17",
"208  2014-247T01:17 2014-278T22:43",
"209  2014-278T22:43 2014-318T23:03",
"210  2014-318T23:03 2014-358T19:16",
"211  2014-358T19:16 2015-025T18:41",
"212  2015-025T18:41 2015-057T17:14",
"213  2015-057T17:14 2015-087T16:40",
"214  2015-087T16:40 2015-115T17:46",
"215  2015-115T17:46 2015-139T04:31",
"216  2015-139T04:31 2015-158T01:48",
"217  2015-158T01:48 2015-176T23:56",
"218  2015-176T23:56 2015-197T08:19",
"219  2015-197T08:19 2015-219T03:41",
"220  2015-219T03:41 2015-240T23:28",
"221  2015-240T23:28 2015-262T19:28",
"222  2015-262T19:28 2015-280T15:12",
"223  2015-280T15:12 2015-294T13:01",
"224  2015-294T13:01 2015-308T10:42",
"225  2015-308T10:42 2015-321T18:22",
"226  2015-321T18:22 2015-334T11:52",
"227  2015-334T11:52 2015-347T05:22",
"228  2015-347T05:22 2015-360T00:24",
"229  2015-360T00:24 2016-007T20:48",
"230  2016-007T20:48 2016-022T05:37",
"231  2016-022T05:37 2016-038T03:23",
"232  2016-038T03:23 2016-058T00:08",
"233  2016-058T00:08 2016-081T22:04",
"234  2016-081T22:04 2016-109T18:23",
"235  2016-109T18:23 2016-141T13:31",
"236  2016-141T13:31 2016-169T06:13",
"237  2016-169T06:13 2016-193T04:17",
"238  2016-193T04:17 2016-212T20:05",
"239  2016-212T20:05 2016-226T15:01",
"240  2016-226T15:01 2016-238T13:51",
"241  2016-238T13:51 2016-250T12:51",
"242  2016-250T12:51 2016-262T12:01",
"243  2016-262T12:01 2016-273T05:54",
"244  2016-273T05:54 2016-282T19:29",
"245  2016-282T19:29 2016-292T09:10",
"246  2016-292T09:10 2016-301T22:45",
"247  2016-301T22:45 2016-311T12:16",
"248  2016-311T12:16 2016-320T09:10",
"249  2016-320T09:10 2016-328T08:21",
"250  2016-328T08:21 2016-335T23:32",
"251  2016-335T23:32 2016-343T03:45",
"252  2016-343T03:45 2016-350T07:57",
"253  2016-350T07:57 2016-357T11:57",
"254  2016-357T11:57 2016-364T15:56",
"255  2016-364T15:56 2017-005T19:49",
"256  2017-005T19:49 2017-012T23:42",
"257  2017-012T23:42 2017-020T03:34",
"258  2017-020T03:34 2017-027T07:29",
"259  2017-027T07:29 2017-034T11:38",
"260  2017-034T11:38 2017-041T16:06",
"261  2017-041T16:06 2017-048T20:28",
"262  2017-048T20:28 2017-056T00:31",
"263  2017-056T00:31 2017-063T04:35",
"264  2017-063T04:35 2017-070T08:31",
"265  2017-070T08:31 2017-077T12:24",
"266  2017-077T12:24 2017-084T16:15",
"267  2017-084T16:15 2017-091T20:06",
"268  2017-091T20:06 2017-099T00:00",
"269  2017-099T00:00 2017-106T04:03",
"270  2017-106T04:03 2017-113T04:16",
"271  2017-113T04:16 2017-119T15:16",
"272  2017-119T15:16 2017-126T02:16",
"273  2017-126T02:16 2017-132T13:10",
"274  2017-132T13:10 2017-139T00:02",
"275  2017-139T00:02 2017-145T11:13",
"276  2017-145T11:13 2017-151T22:44",
"277  2017-151T22:44 2017-158T10:16",
"278  2017-158T10:16 2017-164T21:38",
"279  2017-164T21:38 2017-171T08:58",
"280  2017-171T08:58 2017-177T20:22",
"281  2017-177T20:22 2017-184T07:55",
"282  2017-184T07:55 2017-190T19:28",
"283  2017-190T19:28 2017-197T06:49",
"284  2017-197T06:49 2017-203T18:09",
"285  2017-203T18:09 2017-210T05:30",
"286  2017-210T05:30 2017-216T16:55",
"287  2017-216T16:55 2017-223T04:16",
"288  2017-223T04:16 2017-229T15:24",
"289  2017-229T15:24 2017-236T02:35",
"290  2017-236T02:35 2017-242T13:44",
"291  2017-242T13:44 2017-249T00:54",
"292  2017-249T00:54 2017-255T11:52",
"293  2017-255T11:52 2017-259T10:51");


var sTmp=""
for(var i=0; i < casOrbit.arRaw.length; i++){
  sTmp=casOrbit.arRaw[i].split(/ +/);
  casOrbit.arName[i] = sTmp[0];
  casOrbit.arBeg[i]  = sTmp[1];
  casOrbit.arEnd[i]  = sTmp[2];
}
