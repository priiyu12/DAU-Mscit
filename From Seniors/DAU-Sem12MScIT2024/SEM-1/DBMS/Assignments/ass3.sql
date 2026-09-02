--Assignment 2
--1)

-- CREATE OR REPLACE FUNCTION check_user_id()
-- RETURNS TRIGGER 
-- LANGUAGE plpgsql
-- AS $BODY$
-- BEGIN
    
--     IF EXISTS (SELECT 1 FROM "EC_DB".users WHERE user_id = NEW.user_id) THEN
--         RAISE EXCEPTION 'User ID already exists. Please choose a different ID.';
--     END IF;

--     RETURN NEW;
-- END;
-- $BODY$; 

-- CREATE OR REPLACE TRIGGER trigger_q1
-- BEFORE INSERT ON "EC_DB".users
-- FOR EACH ROW
-- EXECUTE FUNCTION check_user_id();

-- insert into "EC_DB".users values (101,'tmp','tmp@gamil.com','asdfg','tmp','tmp','tmp');
-- select * from "EC_DB".users;

--2)
-- CREATE OR REPLACE FUNCTION check_fk_id()
-- RETURNS TRIGGER 
-- LANGUAGE plpgsql
-- AS $BODY$
-- BEGIN
 
--     IF EXISTS (SELECT 1 FROM "EC_DB".orders WHERE user_id = NEW.user_id) THEN
--         RAISE EXCEPTION 'User ID foreign key already exists.';
--     END IF;
--     RETURN NEW;
-- END;
-- $BODY$;

-- CREATE OR REPLACE TRIGGER trigger_q2
-- BEFORE INSERT ON "EC_DB".orders
-- FOR EACH ROW
-- EXECUTE FUNCTION check_fk_id();
-- insert into "EC_DB".orders values (101,39,'24-07-25','abcdefgh',2525.5,'Pending');
-- select * from "EC_DB".orders;

--3)
-- CREATE OR REPLACE FUNCTION get_disc_price(pro_id INT, disc_per NUMERIC)
-- RETURNS NUMERIC
-- LANGUAGE plpgsql
-- AS $BODY$
-- DECLARE
--     og_price NUMERIC;
--     disc_price NUMERIC;
-- BEGIN
--     SELECT price INTO og_price
--     FROM "EC_DB".products
--     WHERE product_id = pro_id;

--     disc_price = og_price - (og_price * disc_per / 100);

--     RETURN disc_price;
-- END;
-- $BODY$;

-- select * from "EC_DB".products;
-- select get_disc_price(1,5);
--5)

CREATE OR REPLACE FUNCTION dec_stock_qty()
RETURNS TRIGGER 
LANGUAGE plpgsql
AS $BODY$
BEGIN
    
    UPDATE "EC_DB".products
    SET stock_quantity = stock_quantity - NEW.quantity
    WHERE id = NEW.product_id;
    RETURN NEW;
END;
$BODY$;

CREATE OR REPLACE TRIGGER trigger_q5
AFTER INSERT ON "EC_DB".order_details
FOR EACH ROW
EXECUTE FUNCTION dec_stock_qty();

-- SELECT * FROM "EC_DB".ORDER_DETAILS;
-- INSERT INTO "EC_DB".ORDER_DETAILS VALUES (301,1001,1,10,5000)





