#include <gtest/gtest.h>  // gtest must be included first...!
#include <string>
#include <qimessaging/serialization/message.hpp>
#include <qimessaging/datastream.hpp>
#include <qimessaging/reflect.hpp>

//using namespace qi::serialization;


//(ii)
struct Point2D {
public:
  //friend class qi::serialization::serialize<Point2D>;
  Point2D(int x = 0, int y = 0)
    : x(x), y(y)
  {}

//private:
  int x;
  int y;
};

//(ii)
struct TimeStamp {
  int i;
  int j;
};


//((ii)(ii))
struct TimeStampedPoint2D {
  Point2D p;
  TimeStamp t;
};


//namespace qi {
//  namespace serialization {

//  template <>
//  struct serialize<Point2D>  {
//    static inline void write(Message &sd, const Point2D &val) {
//      qi::serialization::serialize<int>::write(val.x);
//      qi::serialization::serialize<int>::write(val.y);
//    }

//    static inline void read(Message &sd, Point2D &val) {
//      qi::serialization::serialize<int>::read(val.x);
//      qi::serialization::serialize<int>::read(val.y);
//    }

//    static inline void signature(std::string &sign) {
//      qi::signatureFromObject::value(val.x, sign);
//      qi::signatureFromObject::value(val.y, sign);
//    }
//  };

//  }
//};



TEST(testSerializable, POD) {
  qi::DataStream  m;
  int i1, i2;

  i1 = 42;

  m << i1;
  m >> i2;

  EXPECT_EQ(i1, i2);
}


#if 0
QI_REFLECT(Point2D, ((int, x)) ((int, y)));
QI_REFLECT(TimeStamp, ((int, i)) ((int, j)));
QI_REFLECT(TimeStampedPoint2D, ((Point2D, p)) ((TimeStamp, t)));



TEST(testSerializable, Point2D) {
  Point2D      in(4, 3);
  Point2D      out;
  qi::DataStream  m;
  qi::DataStream m2;
  TimeStampedPoint2D ti;
  TimeStampedPoint2D to;

  ti.p.x = 1;
  ti.p.y = 2;
  ti.t.i = 3;
  ti.t.j = 4;

  qi::serialization::serialize<Point2D>::write(m, in);
  qi::serialization::serialize<Point2D>::read(m, out);

  qi::serialization::serialize<TimeStampedPoint2D>::write(m2, ti);
  qi::serialization::serialize<TimeStampedPoint2D>::read(m2, to);

  EXPECT_EQ(4, out.x);
  EXPECT_EQ(3, out.y);

  EXPECT_EQ(1, to.p.x);
  EXPECT_EQ(2, to.p.y);
  EXPECT_EQ(3, to.t.i);
  EXPECT_EQ(4, to.t.j);
  EXPECT_STREQ("((ii)(ii))", qi::signatureFromObject::value(ti).c_str());
}

#endif

#if 0
struct Inner : Serializable {
  Inner() : text("hello"), number(42) {}

  std::string text;
  int number;

  void serialize(Serializer& v) {
    v.visit(text);
    v.visit(number);
  }
};


struct Outer : Serializable {
  Outer() : floatNumber(42.2f) {}

  float floatNumber;
  Inner inner;

  void serialize(Serializer& v) {
    v.visit(floatNumber);
    v.visit(inner);
    v.visit(inner);
  }
};

struct Hard : Serializable {
  std::vector<std::map<std::string, int> > content;

  void serialize(Serializer& v) {
     v.visit(content);
  }
};

struct Harder : Serializable {
  std::vector<std::map<std::string, Inner> > content;

  void serialize(Serializer& v) {
     v.visit(content);
  }
};

TEST(testSerializable, simpleStruct) {
  Inner t;
  t.number = 1;
  t.text = "hello world";

  qi::DataStream m;
  Serializer serializer(ACTION_SERIALIZE, m);
  t.serialize(serializer);

  Serializer deserializer(ACTION_DESERIALIZE, m);
  Inner t2;
  t2.serialize(deserializer);
}

TEST(testSerializable, multiLayer) {
  Outer t;
  t.floatNumber = 1.111f;
  t.inner.number = 1;
  t.inner.text = "shtuff";

  qi::DataStream m;
  Serializer serializer(ACTION_SERIALIZE, m);
  t.serialize(serializer);

  Serializer deserializer(ACTION_DESERIALIZE, m);
  Outer t2;
  t2.serialize(deserializer);
}

TEST(testSerializable, hard) {
  Hard t;
  std::vector<std::map<std::string, int> > shtuff;
  std::map<std::string, int> map;
  map.insert(std::make_pair("oink", 1));
  map.insert(std::make_pair("oink2", 2));
  shtuff.push_back(map);
  t.content = shtuff;

  qi::DataStream m;
  Serializer serializer(ACTION_SERIALIZE, m);
  t.serialize(serializer);

  Serializer deserializer(ACTION_DESERIALIZE, m);
  Hard t2;
  t2.serialize(deserializer);
}


TEST(testSerializable, harder) {
  Harder t;
  std::vector<std::map<std::string, Inner> > shtuff;
  std::map<std::string, Inner> map;
  Inner inner1;
  inner1.number = 5;
  Inner inner2;
  inner2.number = 6;
  map.insert(std::make_pair("oink", inner1));
  map.insert(std::make_pair("oink2", inner2));
  shtuff.push_back(map);
  t.content = shtuff;

  qi::DataStream m;
  Serializer serializer(ACTION_SERIALIZE, m);
  t.serialize(serializer);

  Serializer deserializer(ACTION_DESERIALIZE, m);
  Harder t2;
  t2.serialize(deserializer);
}

struct Point2D : Serializable {
  int x;
  int y;

  void serialize(Serializer& s) {
    s.visit(x, y);
  }
};

struct TimeStamp : Serializable {
  int seconds;
  int nanoseconds;

  void serialize(Serializer& s) {
    s.visit(seconds);
    s.visit(nanoseconds);
  }
};

struct StampedPoint2D : Serializable {
  Point2D point;
  TimeStamp time;

  void serialize(Serializer& s) {
    s.visit(point, time);
  }
};

TEST(testSerializable, points) {
  Point2D point;
  point.x = 1;
  point.y = 2;

  TimeStamp timestamp;
  timestamp.seconds = 10001;
  timestamp.nanoseconds = 999;

  StampedPoint2D stampedPoint;
  stampedPoint.point = point;
  stampedPoint.time = timestamp;

  // ---- code that will never be seen, and needs a little clearup
  qi::DataStream pointMessage;
  Serializer s1(ACTION_SERIALIZE, pointMessage);
  point.serialize(s1);

  qi::DataStream stampedPointMessage;
  Serializer s2(ACTION_SERIALIZE, stampedPointMessage);
  stampedPoint.serialize(s2);

  qi::DataStream stampedPointMessageAgain;
  Serializer s3(ACTION_SERIALIZE, stampedPointMessageAgain);
  stampedPoint.serialize(s3);

  // -- Get a Point2D from a Point2D message
  Serializer s4(ACTION_DESERIALIZE, pointMessage);
  Point2D resultPoint1;
  resultPoint1.serialize(s4);

  // -- Get a Point2D from a StampedPoint2D message
  Serializer s5(ACTION_DESERIALIZE, stampedPointMessageAgain);
  Point2D resultPoint2;
  // This only works because the first two serialized fields are x and y
  resultPoint2.serialize(s5);

  // -- Get a StampedPoint2D from a StampedPoint2D message
  Serializer s6(ACTION_DESERIALIZE, stampedPointMessage);
  StampedPoint2D resultStampedPoint;
  resultStampedPoint.serialize(s6);
  // ---------------------------------------------------

  ASSERT_EQ(point.x, resultPoint1.x);
  ASSERT_EQ(point.y, resultPoint1.y);
  ASSERT_EQ(point.x, resultPoint2.x);
  ASSERT_EQ(point.y, resultPoint2.y);
  ASSERT_EQ(point.x, resultStampedPoint.point.x);
  ASSERT_EQ(point.y, resultStampedPoint.point.y);
  ASSERT_EQ(timestamp.seconds, resultStampedPoint.time.seconds);
  ASSERT_EQ(timestamp.nanoseconds, resultStampedPoint.time.nanoseconds);
}

#endif
