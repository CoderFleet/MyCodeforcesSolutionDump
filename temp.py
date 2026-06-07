import cv2
import numpy as np
import os
import sys

def count_intersections(image_path):
    if not os.path.isfile(image_path):
        print(0)
        return

    # Load image in grayscale
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        print(0)
        return

    # 1. Binarize the image (invert so lines/axes are white (255) on black (0))
    _, thresh = cv2.threshold(img, 200, 255, cv2.THRESH_BINARY_INV)

    # 2. Identify and remove horizontal and vertical axes
    # Create long structural elements to match axes spanning across the canvas
    horizontal_kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (40, 1))
    vertical_kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 40))

    detect_horizontal = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, horizontal_kernel, iterations=2)
    detect_vertical = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, vertical_kernel, iterations=2)

    # Subtract the axes from the original thresholded mask to keep only data lines
    clean_lines = cv2.absdiff(thresh, detect_horizontal)
    clean_lines = cv2.absdiff(clean_lines, detect_vertical)
    
    # Clean up minor residual noise fragments from axes intersections
    kernel_clean = cv2.getStructuringElement(cv2.MORPH_RECT, (2, 2))
    clean_lines = cv2.morphologyEx(clean_lines, cv2.MORPH_CLOSE, kernel_clean)

    # 3. Detect intersections using Harris Corner Detection
    # Convert clean_lines to float32 for Harris Algorithm
    gray_float = np.float32(clean_lines)
    
    # blocksize=3, aperture=3, k=0.04
    dst = cv2.cornerHarris(gray_float, blockSize=3, ksize=3, k=0.04)
    
    # Dilate corner points to consolidate local peaks
    dst = cv2.dilate(dst, None)
    
    # Threshold for a optimal corner response
    # Real intersections form a strong cross-pattern yielding high response
    threshold = 0.1 * dst.max()
    corner_coordinates = np.argwhere(dst > threshold)

    # 4. Group adjacent pixel coordinates to count distinct intersection points
    if len(corner_coordinates) == 0:
        print(0)
        return

    distinct_points = []
    min_distance_threshold = 10.0 # Pixel radius distance to merge duplicate responses

    for coord in corner_coordinates:
        pt = np.array([coord[1], coord[0]]) # (x, y) format
        
        # Check if this point is close to an already logged intersection
        is_duplicate = False
        for existing_pt in distinct_points:
            dist = np.linalg.norm(pt - existing_pt)
            if dist < min_distance_threshold:
                is_duplicate = True
                break
                
        if not is_duplicate:
            distinct_points.append(pt)

    # Print the final scalar count to standard output
    print(len(distinct_points))

if __name__ == "__main__":
    # Handle standard input string parsing
    filename = input().strip()
    count_intersections(filename)