grant connect,resource to knaptest identified by knaptest;

grant select,insert,update on knaparticle to knaptest;

grant select,insert,update on knapav10 to knaptest;

grant select,insert,update on knapdev10 to knaptest;

grant select,insert,update on knapdestino to knaptest;

grant select,insert,update on knapinv to knaptest;

grant select,insert,update on knaporder to knaptest;

grant select,insert,update on knaporderlin to knaptest;

grant select,insert,update on knaporderreply to knaptest;

grant select,insert,update on knaporderlinreply to knaptest;

grant select,insert,update on knapstock to knaptest;

grant select,insert,update on knapstorage to knaptest;

grant select,insert,update on knaplock to knaptest;

grant select,insert,update on knapreplylock to knaptest;

create synonym knaptest.h2k for knapdev10;

create synonym knaptest.k2h for knapav10;

create synonym knaptest.article for knaparticle;

create synonym knaptest.wh_order for knaporder;

create synonym knaptest.order_line for knaporderlin;

create synonym knaptest.target_st for knapdestino;

create synonym knaptest.order_reply for knaporderreply;

create synonym knaptest.inventory_snapshot for knapinv;

create synonym knaptest.stock_info for knapstock;

create synonym knaptest.storage_snapshot for knapstorage;

CREATE OR REPLACE SYNONYM knaptest.INVENTORY_SNAPSHOT FOR KNAPINV;

CREATE OR REPLACE SYNONYM knaptest.ORDER_LINE_REPLY FOR KNAPORDERLINREPLY;


CREATE OR REPLACE SYNONYM knaptest.unit_lock_unlock FOR KNAPLOCK;

CREATE OR REPLACE SYNONYM knaptest.REPLY_lock_unlock FOR KNAPREPLYLOCK;
