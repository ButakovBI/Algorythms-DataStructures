from helpers import round_up
from services.database_server import DatabaseServer


def test_database_server_replicas_1():
    database_server = DatabaseServer()
    database_server.update_config(agents=2000, storage=0, traffic=50,
                                  mail_traffic=300, distributed=False, nodes=5)
    config = database_server.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 100
    assert config["cpu"] == 1
    assert config["storage"] == round_up(
        (0.00000002 * 2000 * 2000 + 0.00067749 * 2000 + 4.5) * 2000 / 5, 3)


def test_database_server_replicas_2_memory_1():
    server = DatabaseServer()
    server.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=5)
    config = server.get_config()
    assert config["replicas"] == max(round(2000 / 15000), 1)
    assert config["memory"] == round(500 * 1.6, 3)
    assert config["cpu"] == 1
    assert config["storage"] == round_up(
        (0.00000002 * 2000 * 2000 + 0.00067749 * 2000 + 4.5) * 2000 / 5, 3)


def test_database_server_replicas_3_storage():
    server = DatabaseServer()
    server.update_config(
        agents=0,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = server.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == round(500 * 1.6, 3)
    assert config["cpu"] == 1
    assert config["storage"] == 0
