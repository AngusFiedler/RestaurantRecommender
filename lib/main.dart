import 'package:flutter/material.dart';
import 'package:location/location.dart';
import 'util/jsonUtil.dart';
import 'newItem.dart';
//import 'package:url_launcher/url_launcher.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Food Recommendation',
      theme: ThemeData(
        primarySwatch: Colors.red,
      ),
      home: MyHomePage(title: 'Food Recommendation'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);
  final String title;
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String lat = "Latitude: NULL",
      longitude = "Longitude: NULL";
  Location _location = new Location();

  //refreshes the users current location
  void refreshData() async {
    LocationData userLocation;
    userLocation = await _location.getLocation();
    print(userLocation.latitude);
    print(userLocation.longitude);
    //lat = userLocation.latitude.toString();
    setState(() {
      lat = "Latitude: " + userLocation.latitude.toString();
      longitude = "Longitude: " + userLocation.longitude.toString();
      //JsonUtil().fetchPost();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text(widget.title),
        ),
        body: ListView(
          children: <Widget>[
            Center(
              child: Column(
                children: <Widget>[
                  /*
                  Text(
                    "Top Recommendation",
                    style: TextStyle(fontSize: 25),
                  ),
                  */
                  futureBuilderReco("1.json"),
                  futureBuilderReco("2.json"),
                  futureBuilderReco("3.json"),
                  futureBuilderReco("4.json"),
                  futureBuilderReco("5.json"),
                  myFlatZBtn(),
                  Text(lat),
                  Text(longitude),
                ],
              ),
            ),
          ],
        ),
        floatingActionButton:
            floatingAction() // This trailing comma makes auto-formatting nicer for build methods.
        );
  }

  FutureBuilder<Post> futureBuilderReco(String id) {
    return FutureBuilder<Post>(
      future: JsonUtil().fetchPost(id),
      builder: (context, snapshot) {
        if (snapshot.hasData) {
          return myCard(snapshot);
        } else if (snapshot.hasError) {
          return Text("${snapshot.error}");
        }
        // By default, show a loading spinner
        return CircularProgressIndicator();
      },
    );
  }

  FlatButton myFlatZBtn() {
    return FlatButton(
      child: Text(
        "Refresh Data",
        style: TextStyle(color: Colors.white),
      ),
      onPressed: () {
        refreshData();
      },
      color: Colors.red,
    );
  }

  Card myCard(AsyncSnapshot<Post> post) {
    return Card(
        child: Padding(
      padding: EdgeInsets.all(20),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          recoTextWidget(post),
        ],
      ),
    ));
  }

  FloatingActionButton floatingAction() {
    return FloatingActionButton(
      onPressed: () {
        Navigator.push(
          context,
          MaterialPageRoute(builder: (context) => NewItemWidget()),
        );
      },
      tooltip: 'New Meal',
      child: Icon(Icons.add),
    );
  }

  Widget recoTextWidget(AsyncSnapshot<Post> post) {
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: <Widget>[
        Text(post.data.restaurantName, style: TextStyle(fontSize: 20,fontWeight: FontWeight.bold),),
        Divider(),
        Text("Location: " + post.data.location),
        stars(post.data.rating),
        Text("Rating: " + post.data.rating.toString()),
      ],
    );
  }

  Widget stars(double count) {
    List<Widget> list = new List<Widget>();
    double test;
    for (var i = 0; i < count - 1; i++) {
      list.add(new Icon(
        Icons.star,
        color: Colors.yellow,
      ));
      test = i.toDouble() + 1;
    }
    double result = count - test;
    if (result >= 0.5) {
      list.add(new Icon(
        Icons.star_half,
        color: Colors.yellow,
      ));
    }
    return new Row(children: list);
  }
}
