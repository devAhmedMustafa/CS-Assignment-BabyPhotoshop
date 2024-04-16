# Baby Photoshop

### Tools
- | Qt | 6.5.3 |
- Microsoft Vs 2022
- CLion

___

### **Filters**
1. Grayscale
2. Invert
3. Rotate
4. Flip
5. Black And White
6. Blur
7. Add Frame
8. Resize
9. Noise
10. Oil
11. Bloom
12. Merge 
13. Darken & Brighten 
14. Sunlight 
15. Crop 
16. Detect 
17. Infrared 
18. Gamma 
19. Purple 
20. Skew

___

### New Filters

1. #### Gamma
   • For each pixel in the image:
      • Normalize the color intensity by dividing it by 255.0.
      • Apply gamma correction to the normalized color intensity using the formula: color = pow(color, gamma).
      • Scale the corrected color intensity back to the range [0, 255] and assign it to the pixel.

2. #### Bloom
   1. Create a blurred imaged with radius of 2
   2. Iterate on each pixel
      1. Check if any channel of the pixel colors is greater than the threshold
         1. pixel [r] = min(255, pixel[r] * intensity + blurred [r])
         2. pixel [g] = min(255, pixel[g] * intensity + blurred [g])
         3. pixel [b] = min(255, pixel[b] * intensity + blurred [b])

___

### Sources :
1. #### Video Link
