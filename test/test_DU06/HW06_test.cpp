#define CATCH_CONFIG_MAIN
#define __PROGTEST__

#include "../catch.hpp"

// include proper heading ----------------------------------------------------------------------------------------------
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------

//Include tested file
#include "../../homework/06/test.cpp"





// TESTS ---------------------------------------------------------------------------------------------------------------

TEST_CASE("TEST LEVEL 1", "[PREDEFINED]") {

    CDataTypeStruct a = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct b = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("READY")).
            addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct c = CDataTypeStruct().
            addField("m_First", CDataTypeInt()).
            addField("m_Second", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Third", CDataTypeDouble());

    CDataTypeStruct d = CDataTypeStruct().
            addField("m_Length", CDataTypeInt()).
            addField("m_Status", CDataTypeEnum().
            add("NEW").
            add("FIXED").
            add("BROKEN").
            add("DEAD")).
            addField("m_Ratio", CDataTypeInt());
    REQUIRE (whitespaceMatch(a, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Status;\n"
                                "  double m_Ratio;\n"
                                "}"));

    REQUIRE (whitespaceMatch(b, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    READY\n"
                                "  } m_Status;\n"
                                "  double m_Ratio;\n"
                                "}"));

    REQUIRE (whitespaceMatch(c, "struct\n"
                                "{\n"
                                "  int m_First;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Second;\n"
                                "  double m_Third;\n"
                                "}"));

    REQUIRE (whitespaceMatch(d, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Status;\n"
                                "  int m_Ratio;\n"
                                "}"));

    REQUIRE (a != b);
    REQUIRE (a == c);
    REQUIRE (a != d);
    REQUIRE (a.field("m_Status") == CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD"));
    REQUIRE (a.field("m_Status") != CDataTypeEnum().add("NEW").add("BROKEN").add("FIXED").add("DEAD"));
    REQUIRE (a != CDataTypeInt());
    REQUIRE (whitespaceMatch(a.field("m_Status"), "enum\n"
                                                  "{\n"
                                                  "  NEW,\n"
                                                  "  FIXED,\n"
                                                  "  BROKEN,\n"
                                                  "  DEAD\n"
                                                  "}"));

    CDataTypeStruct aOld = a;
    b.addField("m_Other", CDataTypeDouble());

    a.addField("m_Sum", CDataTypeInt());

    REQUIRE (a != aOld);
    REQUIRE (a != c);
    REQUIRE (aOld == c);
    REQUIRE (whitespaceMatch(a, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Status;\n"
                                "  double m_Ratio;\n"
                                "  int m_Sum;\n"
                                "}"));

    REQUIRE (whitespaceMatch(b, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    READY\n"
                                "  } m_Status;\n"
                                "  double m_Ratio;\n"
                                "  double m_Other;\n"
                                "}"));

    c.addField("m_Another", a.field("m_Status"));

    REQUIRE (whitespaceMatch(c, "struct\n"
                                "{\n"
                                "  int m_First;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Second;\n"
                                "  double m_Third;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Another;\n"
                                "}"));

    d.addField("m_Another", a.field("m_Ratio"));

    REQUIRE (whitespaceMatch(d, "struct\n"
                                "{\n"
                                "  int m_Length;\n"
                                "  enum\n"
                                "  {\n"
                                "    NEW,\n"
                                "    FIXED,\n"
                                "    BROKEN,\n"
                                "    DEAD\n"
                                "  } m_Status;\n"
                                "  int m_Ratio;\n"
                                "  double m_Another;\n"
                                "}"));

    REQUIRE (a.getSize() == 20);
    REQUIRE (b.getSize() == 24);
    try {
        a.addField("m_Status", CDataTypeInt());
        REQUIRE ("addField: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        REQUIRE (e.what() == "Duplicate field: m_Status"sv);
    }

    try {
        cout << a.field("m_Fail") << endl;
        REQUIRE ("field: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        REQUIRE (e.what() == "Unknown field: m_Fail"sv);
    }

    try {
        CDataTypeEnum en;
        en.add("FIRST").
                add("SECOND").
                add("FIRST");
        REQUIRE ("add: missing exception!" == nullptr);
    }
    catch (const invalid_argument &e) {
        REQUIRE (e.what() == "Duplicate enum value: FIRST"sv);
    }

}




TEST_CASE("TEST LEVEL 2", "[PREDEFINED]") {


    CDataTypeStruct  a = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Ratio", CDataTypeDouble () );

    CDataTypeStruct b = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "READY" ) ).
            addField ( "m_Ratio", CDataTypeDouble () );

    CDataTypeStruct c =  CDataTypeStruct () .
            addField ( "m_First", CDataTypeInt () ) .
            addField ( "m_Second", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Third", CDataTypeDouble () );

    CDataTypeStruct  d = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Ratio", CDataTypeInt () );
    REQUIRE ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    REQUIRE ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    REQUIRE ( whitespaceMatch ( c, "struct\n"
                                  "{\n"
                                  "  int m_First;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Second;\n"
                                  "  double m_Third;\n"
                                  "}") );

    REQUIRE ( whitespaceMatch ( d, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  int m_Ratio;\n"
                                  "}") );

    REQUIRE ( a != b );
    REQUIRE ( a == c );
    REQUIRE ( a != d );
    REQUIRE ( a != CDataTypeInt() );
    REQUIRE ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
                                                         "{\n"
                                                         "  NEW,\n"
                                                         "  FIXED,\n"
                                                         "  BROKEN,\n"
                                                         "  DEAD\n"
                                                         "}") );

    b . addField ( "m_Other", a );

    a . addField ( "m_Sum", CDataTypeInt ());

    REQUIRE ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  int m_Sum;\n"
                                  "}") );

    REQUIRE ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      DEAD\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "  } m_Other;\n"
                                  "}") );

    REQUIRE ( whitespaceMatch ( b . field ( "m_Other" ), "struct\n"
                                                        "{\n"
                                                        "  int m_Length;\n"
                                                        "  enum\n"
                                                        "  {\n"
                                                        "    NEW,\n"
                                                        "    FIXED,\n"
                                                        "    BROKEN,\n"
                                                        "    DEAD\n"
                                                        "  } m_Status;\n"
                                                        "  double m_Ratio;\n"
                                                        "}") );

    REQUIRE ( whitespaceMatch ( b . field ( "m_Other" ) . field ( "m_Status" ), "enum\n"
                                                                               "{\n"
                                                                               "  NEW,\n"
                                                                               "  FIXED,\n"
                                                                               "  BROKEN,\n"
                                                                               "  DEAD\n"
                                                                               "}") );

    REQUIRE ( a . getSize () == 20 );
    REQUIRE ( b . getSize () == 32 );
    b . addField ( "m_Other1", b );
    b . addField ( "m_Other2", b );
    b . addField ( "m_Other3", b );
    REQUIRE ( b . field ( "m_Other3" ) . field ( "m_Other2" ) . field ( "m_Other1" ) == b . field ( "m_Other1" ) );

    REQUIRE ( b . getSize () == 256);

    REQUIRE ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      DEAD\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "  } m_Other;\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      READY\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        DEAD\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "    } m_Other;\n"
                                  "  } m_Other1;\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      READY\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        DEAD\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "    } m_Other;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        READY\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "      struct\n"
                                  "      {\n"
                                  "        int m_Length;\n"
                                  "        enum\n"
                                  "        {\n"
                                  "          NEW,\n"
                                  "          FIXED,\n"
                                  "          BROKEN,\n"
                                  "          DEAD\n"
                                  "        } m_Status;\n"
                                  "        double m_Ratio;\n"
                                  "      } m_Other;\n"
                                  "    } m_Other1;\n"
                                  "  } m_Other2;\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      READY\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        DEAD\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "    } m_Other;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        READY\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "      struct\n"
                                  "      {\n"
                                  "        int m_Length;\n"
                                  "        enum\n"
                                  "        {\n"
                                  "          NEW,\n"
                                  "          FIXED,\n"
                                  "          BROKEN,\n"
                                  "          DEAD\n"
                                  "        } m_Status;\n"
                                  "        double m_Ratio;\n"
                                  "      } m_Other;\n"
                                  "    } m_Other1;\n"
                                  "    struct\n"
                                  "    {\n"
                                  "      int m_Length;\n"
                                  "      enum\n"
                                  "      {\n"
                                  "        NEW,\n"
                                  "        FIXED,\n"
                                  "        BROKEN,\n"
                                  "        READY\n"
                                  "      } m_Status;\n"
                                  "      double m_Ratio;\n"
                                  "      struct\n"
                                  "      {\n"
                                  "        int m_Length;\n"
                                  "        enum\n"
                                  "        {\n"
                                  "          NEW,\n"
                                  "          FIXED,\n"
                                  "          BROKEN,\n"
                                  "          DEAD\n"
                                  "        } m_Status;\n"
                                  "        double m_Ratio;\n"
                                  "      } m_Other;\n"
                                  "      struct\n"
                                  "      {\n"
                                  "        int m_Length;\n"
                                  "        enum\n"
                                  "        {\n"
                                  "          NEW,\n"
                                  "          FIXED,\n"
                                  "          BROKEN,\n"
                                  "          READY\n"
                                  "        } m_Status;\n"
                                  "        double m_Ratio;\n"
                                  "        struct\n"
                                  "        {\n"
                                  "          int m_Length;\n"
                                  "          enum\n"
                                  "          {\n"
                                  "            NEW,\n"
                                  "            FIXED,\n"
                                  "            BROKEN,\n"
                                  "            DEAD\n"
                                  "          } m_Status;\n"
                                  "          double m_Ratio;\n"
                                  "        } m_Other;\n"
                                  "      } m_Other1;\n"
                                  "    } m_Other2;\n"
                                  "  } m_Other3;\n"
                                  "}" ) );

    try
    {
        a . addField ( "m_Status", CDataTypeInt () );
        REQUIRE ( "addField: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( e . what () == "Duplicate field: m_Status"sv );
    }

    try
    {
        cout << a . field ( "m_Fail" ) << endl;
        REQUIRE ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( e . what () == "Unknown field: m_Fail"sv );
    }

    try
    {
        cout << a . field ( "m_Length" ) . field ( "m_Foo" ) << endl;
        REQUIRE ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( whitespaceMatch ( e . what (), "Cannot use field() for type: int" ));
    }

    try
    {
        cout << a . field ( "m_Status" ) . field ( "m_Foo" ) << endl;
        REQUIRE ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( whitespaceMatch ( e . what (), "Cannot use field() for type: enum\n"
                                                "{\n"
                                                "  NEW,\n"
                                                "  FIXED,\n"
                                                "  BROKEN,\n"
                                                "  DEAD\n"
                                                "}" ));
    }

    try
    {
        CDataTypeEnum en;
        en . add ( "FIRST" ) .
                add ( "SECOND" ) .
                add ( "FIRST" );
        REQUIRE ( "add: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( e . what () == "Duplicate enum value: FIRST"sv );
    }

    CDataTypeArray ar1 ( 10, CDataTypeInt () );
    REQUIRE ( whitespaceMatch ( ar1, "int[10]") );
    REQUIRE ( whitespaceMatch ( ar1 . element (), "int") );
    CDataTypeArray ar2 ( 11, ar1 );
    REQUIRE ( whitespaceMatch ( ar2, "int[11][10]") );
    REQUIRE ( whitespaceMatch ( ar2 . element (), "int[10]") );
    REQUIRE ( whitespaceMatch ( ar2 . element () . element (), "int") );
    CDataTypeArray ar3 ( 10, CDataTypeArray ( 20, CDataTypePtr ( CDataTypeInt () ) ) );
    REQUIRE ( whitespaceMatch ( ar3, "int*[10][20]") );
    REQUIRE ( whitespaceMatch ( ar3 . element (), "int*[20]") );
    REQUIRE ( whitespaceMatch ( ar3 . element () . element (), "int*") );
    REQUIRE ( whitespaceMatch ( ar3 . element () . element () . element (), "int") );
    CDataTypePtr ar4  ( ar1 . element () );
    REQUIRE ( whitespaceMatch ( ar4, "int*") );
    REQUIRE ( whitespaceMatch ( ar4 . element (), "int") );
    CDataTypePtr ar5  ( b . field ( "m_Status" ) );
    REQUIRE ( whitespaceMatch ( ar5, "enum\n"
                                    "{\n"
                                    "  NEW,\n"
                                    "  FIXED,\n"
                                    "  BROKEN,\n"
                                    "  READY\n"
                                    "}*") );
    REQUIRE ( whitespaceMatch ( ar5 . element (), "enum\n"
                                                 "{\n"
                                                 "  NEW,\n"
                                                 "  FIXED,\n"
                                                 "  BROKEN,\n"
                                                 "  READY\n"
                                                 "}") );
    CDataTypePtr ar6 ( ar3 . element () . element () );
    REQUIRE ( whitespaceMatch ( ar6, "int**") );
    REQUIRE ( whitespaceMatch ( ar6 . element (), "int*") );
    REQUIRE ( whitespaceMatch ( ar6 . element () . element (), "int") );
    CDataTypePtr ar7 ( CDataTypeArray ( 50, ar6 ) );
    REQUIRE ( whitespaceMatch ( ar7, "int**(*)[50]") );
    REQUIRE ( whitespaceMatch ( ar7 . element (), "int**[50]") );
    REQUIRE ( whitespaceMatch ( ar7 . element () . element (), "int**") );
    REQUIRE ( whitespaceMatch ( ar7 . element () . element () . element (), "int*") );
    REQUIRE ( whitespaceMatch ( ar7 . element () . element () . element () . element (), "int") );
    CDataTypeArray ar8 ( 25, ar7 );
    REQUIRE ( whitespaceMatch ( ar8, "int**(*[25])[50]") );
    CDataTypePtr ar9 ( ar8 );
    REQUIRE ( whitespaceMatch ( ar9, "int**(*(*)[25])[50]") );
    a . addField ( "m_Ar1", ar1 ) .
            addField ( "m_Ar2", ar2 ) .
            addField ( "m_Ar3", ar3 ) .
            addField ( "m_Ar4", ar4 ) .
            addField ( "m_Ar5", ar5 ) .
            addField ( "m_Ar6", ar6 ) .
            addField ( "m_Ar7", ar7 ) .
            addField ( "m_Ar8", ar8 ) .
            addField ( "m_Ar9", ar9 );
    REQUIRE ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  int m_Sum;\n"
                                  "  int m_Ar1[10];\n"
                                  "  int m_Ar2[11][10];\n"
                                  "  int* m_Ar3[10][20];\n"
                                  "  int* m_Ar4;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  }* m_Ar5;\n"
                                  "  int** m_Ar6;\n"
                                  "  int**(* m_Ar7)[50];\n"
                                  "  int**(* m_Ar8[25])[50];\n"
                                  "  int**(*(* m_Ar9)[25])[50];\n"
                                  "}") );
    a . addField ( "m_Madness", CDataTypeArray ( 40, CDataTypePtr ( a ) ) );
    REQUIRE ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  int m_Sum;\n"
                                  "  int m_Ar1[10];\n"
                                  "  int m_Ar2[11][10];\n"
                                  "  int* m_Ar3[10][20];\n"
                                  "  int* m_Ar4;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  }* m_Ar5;\n"
                                  "  int** m_Ar6;\n"
                                  "  int**(* m_Ar7)[50];\n"
                                  "  int**(* m_Ar8[25])[50];\n"
                                  "  int**(*(* m_Ar9)[25])[50];\n"
                                  "  struct\n"
                                  "  {\n"
                                  "    int m_Length;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      DEAD\n"
                                  "    } m_Status;\n"
                                  "    double m_Ratio;\n"
                                  "    int m_Sum;\n"
                                  "    int m_Ar1[10];\n"
                                  "    int m_Ar2[11][10];\n"
                                  "    int* m_Ar3[10][20];\n"
                                  "    int* m_Ar4;\n"
                                  "    enum\n"
                                  "    {\n"
                                  "      NEW,\n"
                                  "      FIXED,\n"
                                  "      BROKEN,\n"
                                  "      READY\n"
                                  "    }* m_Ar5;\n"
                                  "    int** m_Ar6;\n"
                                  "    int**(* m_Ar7)[50];\n"
                                  "    int**(* m_Ar8[25])[50];\n"
                                  "    int**(*(* m_Ar9)[25])[50];\n"
                                  "  }* m_Madness[40];\n"
                                  "}") );
    REQUIRE ( a . field ( "m_Madness" ) . element () . element () . field ( "m_Ar9" ) == a . field ( "m_Ar9" ));
    REQUIRE ( a . field ( "m_Madness" ) . element () . element () . field ( "m_Ar9" ) != a . field ( "m_Ar8" ));
    try
    {
        cout << ar2 . field ( "m_Foo" ) << endl;
        REQUIRE ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( whitespaceMatch ( e . what (), "Cannot use field() for type: int[11][10]" ));
    }

    try
    {
        cout << c . element () << endl;
        REQUIRE ( "element: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        REQUIRE ( whitespaceMatch ( e . what (), "Cannot use element() for type: struct\n"
                                                "{\n"
                                                "  int m_First;\n"
                                                "  enum\n"
                                                "  {\n"
                                                "    NEW,\n"
                                                "    FIXED,\n"
                                                "    BROKEN,\n"
                                                "    DEAD\n"
                                                "  } m_Second;\n"
                                                "  double m_Third;\n"
                                                "}" ));
    }
}
