#define MAXENTRIES 10

#define PI    3.141592654
#define JDIP  9.6
#define RPD   0.0174532925
#define DPR  57.295779506

#define True  1
#define False 0

#define Geographic           0
#define Ecliptic             1
#define Equatorial           2
#define CoRotational         3
#define SaturnSolarMagnetic  4

#define Juno       -61
#define Cassini    -82
#define Ulysses    -55
#define Galileo    -77
#define Voyager1   -31
#define Voyager2   -32

#define Sun         10
#define Venus      299
#define Earth      399
#define Jupiter    599
#define Saturn     699
#define SaturnBC     6

#define Io         501
#define Europa     502
#define Ganymede   503
#define Callisto   504

#define Mimas      601
#define Enceladus  602
#define Tethys     603
#define Dione      604
#define Rhea       605
#define Titan      606
#define Hyperion   607
#define Iapetus    608
#define Phoebe     609
#define Helene     612
#define Telesto    613
#define Methone    632
#define Pallene    633
#define Anthe      649

#define RAU         149600000.0

#define RVenus           6051.8
#define REarth           6378.14
#define RJupiter        71492.0
#define RSaturn         60268.0
#define RSaturnOneBar   60268.0
#define RSaturnOptical  60430.0
#define RSaturnRing     60330.0

#define RIo              1824.4
#define REuropa          1562.68
#define RGanymede        2632.4
#define RCallisto        2409.3

#define RMimas            202.1
#define REnceladus        254.0
#define RTethys           535.8
#define RDione            562.4
#define RRhea             764.8
#define RTitan           2575.0
#define RHyperion         147.0
#define RIapetus          747.4
#define RPhoebe           112.0
#define RHelene            16.0
#define RTelesto           12.0
#define RMethone           10.0
#define RPallene           10.0
#define RAnthe              1.0

typedef struct
{
   char *name;
   char *val;
}
entry;

struct data_struc
{
   int dy1958;
   float spec_den;
   double time_ms;
   double msday;
};

struct time_struc
{
   int st_past;
   int sp_past;
   int st_year;
   int sp_year;
   int st_day;
   int sp_day;
   int st_hr;
   int sp_hr;
   int st_mn;
   int sp_mn;
   int target;
   int observer;
   int BodyName;
   int coord;
   float st_sec;
   float sp_sec;
   double st_total_ms;
   double sp_total_ms;
   double deltatee;
   double radius;
};
