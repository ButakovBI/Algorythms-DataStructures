from helpers import round_up
from services.server import Server


def test_server_replicas_1():
    server = Server()
    server.update_config(
        agents=2000,
        storage=0,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5,
        p3value=3.5)
    config = server.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 100
    assert config["cpu"] == 1
    assert config["storage"] == round_up((0.0019 * 2000 + 2.3154), 3)


def test_server_replicas_2_memory_1():
    server = Server()
    server.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5,
        p3value=3.5)
    config = server.get_config()
    assert config["replicas"] == min(3.5, 2)
    assert config["memory"] == 100
    assert config["cpu"] == 1
    assert config["storage"] == round_up((0.0019 * 2000 + 2.3154), 3)


def test_server_memory_2():
    server = Server()
    server.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=5,
        p3value=3.5)
    config = server.get_config()
    assert config["replicas"] == min(3.5, 2)
    assert config["memory"] == round(50 * 0.5, 3)
    assert config["cpu"] == 1
    assert config["storage"] == round_up((0.0019 * 2000 + 2.3154), 3)


def test_server_nodes():
    server = Server()
    server.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0,
        p3value=3.5)
    config = server.get_config()
    assert config["replicas"] == min(3.5, 2)
    assert config["memory"] == round(50 * 0.5, 3)
    assert config["cpu"] == 1
    assert config["storage"] == 0
