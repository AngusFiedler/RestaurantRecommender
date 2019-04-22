import 'package:flutter/material.dart';
import 'util/jsonUtil.dart';
//import 'package:shared_preferences/shared_preferences.dart';

class NewItemWidget extends StatefulWidget {
  NewItemWidget({Key key}) : super(key: key);
  @override
  _ItemState createState() => new _ItemState();
}

class _ItemState extends State<NewItemWidget> {
  TextEditingController restaurantNameController = new TextEditingController();

  void addData(String restaurantName) async {
    JsonUtil().createPost(restaurantName);
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
              TextField(
                controller: restaurantNameController,
              ),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              Padding(
                padding: EdgeInsets.all(10),
              ),
              saveBtn(),
            ],
          ),
        ));
  }

  Widget saveBtn() {
    return FlatButton(
      child: Text(
        "Save Data",
        style: TextStyle(color: Colors.white),
      ),
      onPressed: () {
        addData(restaurantNameController.text);
        print(restaurantNameController.text);
      },
      color: Colors.red,
    );
  }
}
