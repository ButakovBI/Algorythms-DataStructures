from helpers import round_up
from services.synchronizer import Synchronizer


def test_synchronizer_not_distributed():
    synchronizer = Synchronizer()
    synchronizer.update_config(
        agents=2500,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = synchronizer.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 100
    assert config["cpu"] == 1
    assert config["storage"] == 0


def test_synchronizer_distributed():
    synchronizer = Synchronizer()
    synchronizer.update_config(
        agents=2500,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = synchronizer.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == round_up(500 / 5000, 3) * 1.6
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0002 * 2500 + 0.6, 3)


def test_synchronizer_replicas():
    synchronizer = Synchronizer()
    synchronizer.update_config(
        agents=0,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = synchronizer.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == round_up(500 / 5000, 3) * 1.6
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0002 * 0 + 0.6, 3)
