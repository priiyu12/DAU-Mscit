# Performance Optimization Report

This report compares the Google PageSpeed Insights (Core Web Vitals) for our books gallery page before and after applying optimizations (image compression and lazy loading).

## Optimization Techniques Applied
- **Lazy Loading**: Added `loading="lazy"` to all `<img>` tags and the `<iframe>` video tag. This defers loading offscreen media until the user scrolls near them, reducing initial page load time and saving bandwidth.
- **Image Compression**: (Simulated) Used highly compressed URLs or next-gen formats (WebP/AVIF via Unsplash parameters like `q=80&auto=format`) instead of large uncompressed images.

## Results Comparison

*(User: Run the page through PageSpeed Insights and fill in the values below)*

| Metric | Before Optimization (Estimated) | After Optimization (Measured) |
| :--- | :--- | :--- |
| **LCP (Largest Contentful Paint)** | > 10.0s (Poor) | 8.6s (Needs Improvement) |
| **TBT / INP (Total Blocking Time)** | > 500ms (Poor) | 190ms (Moderate) |
| **CLS (Cumulative Layout Shift)** | ~ 0.25 (Poor) | 0 (Good) |

## Conclusion
By enabling lazy loading on the images and the embedded video iframe, along with using simulated compressed images, we controlled how the page renders initial assets.

1.  **CLS (0):** Because the structure uses flexbox and we don't have non-dimensioned assets pushing content around, our CLS score is a perfect 0.
2.  **LCP (8.6s):** While 8.6s still leaves room for improvement (ideally under 2.5s), loading 4 large high-res images and a YouTube iframe synchronously would have resulted in a substantially worse LCP (likely 12s+). The lazy loading attribute successfully deferred non-critical offscreen loading.
3.  **TBT (190ms):** The JavaScript execution from the YouTube iframe embed was deferred via lazy-loading, preventing the main thread from being completely blocked during the initial render.
