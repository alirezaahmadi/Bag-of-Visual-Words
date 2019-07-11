#include <include/BinLib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void html_print(string input_image, size_t results_bests, int argc) {
  BinIf bin;

  std::vector<HistImage> im_hist =
      bin.ReadBinaryHistImage("../sifts/results.bin");

  ofstream myfile;
  myfile.open("../html/report.html");
  // start HTML
  myfile << "<!DOCTYPE html><html>";

  // Header
  myfile << "<head>" << endl;
  myfile << "<style>" << endl;
  myfile << "p { font-family: arial; font-size: 125%; style='white-space: "
            "nowrap;'>43,560 }"
         << endl;
  myfile << "code { font-size: 125% }" << endl;
  myfile << "</style>" << endl;
  myfile << "<script src='http://maps.google.com/maps/api/js?sensor=false' "
            "type='text/javascript'></script>"
         << endl;
  myfile << "</head>" << endl;
  myfile << "<body>" << endl;

  // Heading
  myfile << "<h2> Result --- Bag of words </h2>" << endl;
  myfile << "<h3> Team: Alireza Ahmadi, Robin Steffens </h3>" << endl;
  myfile << "<br>" << endl;
  myfile << "<br>" << endl;

  if (argc == 4) {
    // Input image
myfile << "<p> Input image: <code>" << input_image << "</code> </p>"
           << endl;
    myfile << "<table style='width:100%'>" << endl;
    myfile << " <col width='500'> " << endl;
    myfile << "  <col width='500'>  " << endl;
    myfile << "<tr>" << endl;
    myfile << "<td><img src='../img/" << input_image
           << "' alt='Input image' "
              "style='width:500px';></td>"
           << endl;

    myfile << "<td>" << endl;
    myfile << "    <div id='map' "
              "style='width:500px;height:375px;background:yellow'></div> "
           << endl;
    myfile << "<script type='text/javascript'>" << endl;

    myfile << "   var locations = [" << endl;
    for (size_t i = 0; i < results_bests; i++) {
      if (i == results_bests - 1) {
        myfile << "[ 'Nearest Image " << i << "', " << im_hist[i].latitude
               << ", " << im_hist[i].longitude << ", " << i << "]" << endl;
      } else {
        myfile << "[ 'Nearest Image " << i << "', " << im_hist[i].latitude
               << ", " << im_hist[i].longitude << ", " << i << "]," << endl;
      }
    }
    myfile << "];" << endl;

    myfile
        << "    var map = new google.maps.Map(document.getElementById('map'), {"
        << endl;
    myfile << "     zoom: 14," << endl;
    myfile << "    center: new google.maps.LatLng(" << im_hist[0].latitude << ", " << im_hist[0].longitude << ")," << endl;
    myfile << "    mapTypeId: google.maps.MapTypeId.ROADMAP" << endl;
    myfile << "  });" << endl;

    myfile << "  var infowindow = new google.maps.InfoWindow();" << endl;

    myfile << "  var marker, i;" << endl;

    myfile << "  for (i = 0; i < locations.length; i++) { " << endl;
    myfile << "    marker = new google.maps.Marker({" << endl;
    myfile << "      position: new google.maps.LatLng(locations[i][1], "
              "locations[i][2]),"
           << endl;
    myfile << "      map: map" << endl;
    myfile << "   });" << endl;

    myfile << "    google.maps.event.addListener(marker, 'click', "
              "(function(marker, i) {"
           << endl;
    myfile << "      return function() {" << endl;
    myfile << "      infowindow.setContent(locations[i][0]);" << endl;
    myfile << "      infowindow.open(map, marker);" << endl;
    myfile << "    }" << endl;
    myfile << "  })(marker, i));" << endl;
    myfile << "  }" << endl;
    myfile << "</script> " << endl;

    myfile << "</td>" << endl;
    myfile << "</tr>" << endl;
    myfile << "</table>" << endl;

    myfile << "<br>" << endl;
    myfile << "<br>" << endl;
    myfile << "<br>" << endl;
  } else if (argc == 5) {
    // Input image
    myfile << "<p> Input image: <code>" << input_image << "</code> </p>"
           << endl;
    myfile << "<table style='width:100%'>" << endl;
    myfile << " <col width='500'> " << endl;
    myfile << "  <col width='500'>  " << endl;
    myfile << "<tr>" << endl;
    myfile << "<td><img src='../data1/" << input_image
           << "' alt='Input image' "
              "style='width:500px';></td>"
           << endl;

    myfile << "<td>" << endl;
    myfile << "    <div id='map' "
              "style='width:500px;height:375px;background:yellow'></div> "
           << endl;
    myfile << "<script type='text/javascript'>" << endl;

    myfile << "   var locations = [" << endl;
    for (size_t i = 0; i < results_bests; i++) {
      if (i == results_bests - 1) {
        myfile << "[ 'Nearest Image " << i << "', " << im_hist[i].latitude
               << ", " << im_hist[i].longitude << ", " << i << "]" << endl;
      } else {
        myfile << "[ 'Nearest Image " << i << "', " << im_hist[i].latitude
               << ", " << im_hist[i].longitude << ", " << i << "]," << endl;
      }
    }
    myfile << "];" << endl;

    myfile
        << "    var map = new google.maps.Map(document.getElementById('map'), {"
        << endl;
    myfile << "     zoom: 14," << endl;
    myfile << "    center: new google.maps.LatLng(" << im_hist[0].latitude << ", " << im_hist[0].longitude << ")," << endl;
    myfile << "    mapTypeId: google.maps.MapTypeId.ROADMAP" << endl;
    myfile << "  });" << endl;

    myfile << "  var infowindow = new google.maps.InfoWindow();" << endl;

    myfile << "  var marker, i;" << endl;

    myfile << "  for (i = 0; i < locations.length; i++) { " << endl;
    myfile << "    marker = new google.maps.Marker({" << endl;
    myfile << "      position: new google.maps.LatLng(locations[i][1], "
              "locations[i][2]),"
           << endl;
    myfile << "      map: map" << endl;
    myfile << "   });" << endl;

    myfile << "    google.maps.event.addListener(marker, 'click', "
              "(function(marker, i) {"
           << endl;
    myfile << "      return function() {" << endl;
    myfile << "      infowindow.setContent(locations[i][0]);" << endl;
    myfile << "      infowindow.open(map, marker);" << endl;
    myfile << "    }" << endl;
    myfile << "  })(marker, i));" << endl;
    myfile << "  }" << endl;
    myfile << "</script> " << endl;

    myfile << "</td>" << endl;
    myfile << "</tr>" << endl;
    myfile << "</table>" << endl;

    myfile << "<br>" << endl;
    myfile << "<br>" << endl;
    myfile << "<br>" << endl;
  }
  // myfile << "  " << endl;

  myfile << "<table style='width:100%'>" << endl;
  myfile << " <col width='50'> " << endl;
  myfile << "  <col width='500'>  " << endl;

  for (size_t i = 0; i < results_bests - 1; i++) {
    myfile << "<tr>" << endl;
    myfile << "<td><p> Nearest Image " << i + 1 << ": <code>" << im_hist[i].name
           << "</code></p></td>" << endl;
    myfile << "<td rowspan='4'> <img src='../data1/" << im_hist[i].name
           << ".png"
           << "' alt='Image' style='width:50%';></td>" << endl;
    myfile << "</tr>" << endl;

    myfile << "<tr>" << endl;
    myfile << "<td><p> Cosine-Comparison: <code> " << im_hist[i].CosCom
           << "</code> </p></td>" << endl;
    myfile << "</tr>" << endl;

    myfile << "<tr>" << endl;
    myfile << "<td><p> Latitude: <code> " << im_hist[i].latitude
           << "</code> </p></td>" << endl;
    myfile << "</tr>" << endl;

    myfile << "<tr>" << endl;
    myfile << "<td><p> Longitude: <code> " << im_hist[i].longitude
           << "</code> </p></td>" << endl;
    myfile << "</tr>" << endl;
  }
  myfile << "</table>" << endl;

  // ending html
  myfile << "</body></html> " << endl;
  myfile.close();

  cout << ">>>>>>>>>> HTML printed <<<<<<<<<<" << endl;
}
