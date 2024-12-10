from helpers import round_up
from services.clickhouse import Clickhouse


def test_clickhouse_not_distributed():
    clickhouse = Clickhouse()
    clickhouse.update_config(agents=2000, storage=0, traffic=50,
                             mail_traffic=300, distributed=False, nodes=5)
    config = clickhouse.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 100
    assert config["cpu"] == 1
    assert config["storage"] == 0


def test_clickhouse_distributed():
    clickhouse = Clickhouse()
    clickhouse.update_config(agents=2000, storage=500, traffic=50,
                             mail_traffic=300, distributed=True, nodes=5)
    config = clickhouse.get_config()
    assert config["replicas"] == max(round(2000 / 15000), 1)
    assert config["memory"] == round(500 * 1.6, 3)
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0000628 * 2000 + 0.6377, 3)


def test_clickhouse_replicas():
    clickhouse = Clickhouse()
    clickhouse.update_config(agents=0, storage=500, traffic=50,
                             mail_traffic=300, distributed=True, nodes=0)
    config = clickhouse.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == round(500 * 1.6, 3)
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0000628 * 0 + 0.6377, 3)
