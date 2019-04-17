import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class NewItemWidget extends StatefulWidget {
  NewItemWidget({Key key}) : super(key: key);
  @override
  _ItemState createState() => new _ItemState();
}

class _ItemState extends State<NewItemWidget> {

  void addData(String restaurantName, String category) async{
    SharedPreferences prefs = await SharedPreferences.getInstance();
    List<String> restaurantNameList = prefs.getStringList("RestaurantNameKey");
    //List<String> restaurantNameList = prefs.getStringList("RestaurantNameKey");
    restaurantNameList.add(restaurantName);
    prefs.setStringList("RestaurantNameKey", restaurantNameList);
  }

  @override
  Widget build(BuildContext context) {
    return new Scaffold(
      appBar: new AppBar(
        title: new Text("New Meal!"),
      ),
      body: Center(
        child: Column(
          children: <Widget>[
            buildCard(),
            Padding(
              padding: EdgeInsets.all(10),
            ),
            //Checkbox(),
          ],
        ),
      ),
    );
  }

  Widget buildCard() {
    return Card(
        margin: EdgeInsets.all(10),
        child: Padding(
          padding: EdgeInsets.all(20),
          child: Column(
            children: <Widget>[
              Text("What Restaurant did you go to?"),
              TextField(),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              Text("What category was this restaurant?"),
              TextField(),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              FlatButton(
                child: Text(
                  "Save Data",
                  style: TextStyle(color: Colors.white),
                ),
                onPressed: () {},
                color: Colors.red,
              ),
            ],
          ),
        ));
  }
}
