import 'package:flutter/material.dart';
import 'package:location/location.dart';
import 'newItem.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
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
  Location _location = new Location();


  void refreshData() async{
    LocationData userLocation;
    userLocation = await _location.getLocation();
    print(userLocation.latitude);
    print(userLocation.longitude);
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
            Card(
                child: Padding(
              padding: EdgeInsets.all(20),
              child: Column(
                children: <Widget>[
                  Text(
                    "Top Recommendation",
                    style: TextStyle(fontSize: 25),
                  ),
                  Divider(),
                  recoTextWidget(),
                ],
              ),
            )
            ),
            FlatButton(child: Text("Refresh Data", style: TextStyle(color: Colors.white),),onPressed: () {refreshData();},color: Colors.red,),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.push(
            context,
            MaterialPageRoute(builder: (context) => NewItemWidget()),
          );
        },
        tooltip: 'New Meal',
        child: Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }

  Widget recoTextWidget(){
    return Column(
      children: <Widget>[
        Text("1. INSERT HERE"),
        Divider(),
        Text("2. INSERT HERE"),
        Divider(),
        Text("3. INSERT HERE"),
        Divider(),
        Text("4. INSERT HERE"),
        Divider(),
        Text("5. INSERT HERE"),

      ],
    );
  }
}
