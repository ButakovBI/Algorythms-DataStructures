from helpers import round_up
from services.scanner import Scanner


def test_scanner_not_distributed():
    scanner = Scanner()
    scanner.update_config(
        agents=2500,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = scanner.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 300
    assert config["cpu"] == 1
    assert config["storage"] == 0


def test_scanner_distributed():
    scanner = Scanner()
    scanner.update_config(
        agents=2500,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = scanner.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 300
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0002 * 2500 + 0.6, 3)


def test_scanner_replicas():
    scanner = Scanner()
    scanner.update_config(
        agents=0,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = scanner.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 300
    assert config["cpu"] == 1
    assert config["storage"] == round_up(0.0002 * 0 + 0.6, 3)
