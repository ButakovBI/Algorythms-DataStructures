from helpers import round_up
from services.kafka import Kafka


def test_kafka_not_distributed():
    kafka = Kafka()
    kafka.update_config(
        agents=2500,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = kafka.get_config()
    assert config["replicas"] == 1
    assert config["memory"] == 100
    assert config["cpu"] == round_up((0.000169 * 2500 + 0.437923) * 5 / 3, 2)
    assert config["storage"] == round_up((0.0004 * 2500 + 0.3231), 3)


def test_kafka_distributed():
    kafka = Kafka()
    kafka.update_config(
        agents=2500,
        mail_traffic=300,
        distributed=True,
        nodes=5)
    config = kafka.get_config()
    assert config["replicas"] == 3
    assert config["memory"] == 300 * 0.5
    assert config["cpu"] == round_up((0.000169 * 2500 + 0.437923) * 5 / 3, 2)
    assert config["storage"] == round_up((0.0004 * 2500 + 0.3231), 3)
