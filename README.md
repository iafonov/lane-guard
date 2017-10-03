## Lane Departure Warning

Code can be linked as part of an iOS application or run as a standalone desktop application (for debug purposes). 

Performs well in real time on iPhone 6.

Built for own entertaiment.

### Approach 

↓ Setup perspective  
↓ Feed frame from file or camera  
↓ Warp perspective (road → screen)  
↓ Grayscale  
↓ Blur  
↓ Canny  
↓ Hough lines  
↓ Detect lanes  
↓ Unwrap perspective for lane points coordinates (screen → road)  
↓ Get distance from car bounds to lanes (in inches)  
↓ Process data, update state, fire events to outside world  
↺ Repeat  

### Demo 

City:  
![day](https://user-images.githubusercontent.com/32007/31109907-e77f6d6a-a7b7-11e7-8fb6-f4883101faef.gif)

Highway:  
![straight_night](https://user-images.githubusercontent.com/32007/31109908-e781d3e8-a7b7-11e7-8319-58f6ee2cc9c1.gif)

Changing lane:  
![changing_lane](https://user-images.githubusercontent.com/32007/31109905-e7649d78-a7b7-11e7-99ff-6544f376335c.gif)

Taking exit:  
![taking_exit](https://user-images.githubusercontent.com/32007/31109909-e78543f2-a7b7-11e7-9c7b-7bd80fed637d.gif)

Perspective transform/dashboard:  
![perspective2](https://user-images.githubusercontent.com/32007/31110047-0fddadc0-a7b9-11e7-8281-b78bf8ea53c8.gif)

Enjoy!
