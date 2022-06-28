import 'package:electric_bike/home.dart';
import 'package:electric_bike/splash_screen.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'firebase_options.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(
    options: DefaultFirebaseOptions.currentPlatform,
  );
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    SystemChrome.setEnabledSystemUIMode(SystemUiMode.leanBack);

    return MaterialApp(
      
      debugShowCheckedModeBanner: false,
      title: 'Electric Bike',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: MyCustomSplashScreen(),
    );
  }
}
