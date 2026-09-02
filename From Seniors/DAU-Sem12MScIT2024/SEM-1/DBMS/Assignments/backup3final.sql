-- SELECT o.user_id
-- FROM "EC_DB".orders o
-- GROUP BY o.user_id
-- HAVING COUNT(DISTINCT o.category_id) = (SELECT COUNT(*) FROM "EC_DB".categories);
-- SELECT o.user_id
-- FROM "EC_DB".orders o
-- JOIN "EC_DB".order_details od ON o.order_id = od.order_id
-- JOIN "EC_DB".products p ON od.product_id = p.product_id
-- GROUP BY o.user_id
-- HAVING COUNT(DISTINCT p.category_id) = (SELECT COUNT(*) FROM "EC_DB".categories);
SELECT DISTINCT o.user_id
FROM "EC_DB".orders o
WHERE o.order_date >= CURRENT_DATE - INTERVAL '30 days'  -- Orders in the last 30 days
AND o.user_id NOT IN (
    SELECT o2.user_id
    FROM "EC_DB".orders o2
    WHERE o2.order_date >= CURRENT_DATE - INTERVAL '7 days'  -- Exclude users with orders in the last 7 days
);


