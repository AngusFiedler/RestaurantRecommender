import 'package:flutter/material.dart';
import 'package:location/location.dart';
import 'util/jsonUtil.dart';
import 'newItem.dart';
import 'dart:async';
import 'dart:convert';
import 'package:http/http.dart' as http;

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
      longitude = "Longitude: NULL",
      speed = "Speed: ";
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
      speed = "Speed: " + userLocation.speed.toString();
      JsonUtil().fetchPost();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text(widget.title),
        ),
        body: Center(
          child: Column(
            //mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              FutureBuilder<Post>(
                future: JsonUtil().fetchPost(),
                builder: (context, snapshot) {
                  if (snapshot.hasData) {
                    //return Text(snapshot.data.body);
                    return myCard(snapshot);
                  } else if (snapshot.hasError) {
                    return Text("${snapshot.error}");
                  }
                  // By default, show a loading spinner
                  return CircularProgressIndicator();
                },
              ),
              FlatButton(
                child: Text(
                  "Refresh Data",
                  style: TextStyle(color: Colors.white),
                ),
                onPressed: () {
                  refreshData();
                },
                color: Colors.red,
              ),
              Text(lat),
              Text(longitude),
              Text(speed),
            ],
          ),
        ),
        floatingActionButton:
            floatingAction() // This trailing comma makes auto-formatting nicer for build methods.
        );
  }

  Card myCard(AsyncSnapshot<Post> post) {
    return Card(
        child: Padding(
      padding: EdgeInsets.all(20),
      child: Column(
        children: <Widget>[
          Text(
            "Top Recommendation",
            style: TextStyle(fontSize: 25),
          ),
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
      children: <Widget>[
        Divider(),
        Text(post.data.id.toString()),
        Divider(),
        Text(post.data.title),
        Divider(),
        Text(post.data.body),
        Divider(),
        Text("4. INSERT HERE"),
        Divider(),
        Text("5. INSERT HERE"),
      ],
    );
  }
}
