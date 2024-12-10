import math

from helpers import round_up
from services.processor import Processor


def test_processor_replicas_1():
    processor = Processor()
    processor.update_config(
        agents=2000,
        storage=0,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = processor.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 100
    assert config["cpu"] == 3
    assert config["storage"] == round_up(-4.25877 +
                                         0.98271 * math.log(2000), 3)


def test_processor_replicas_2_memory():
    processor = Processor()
    processor.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=False,
        nodes=5)
    config = processor.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 100
    assert config["cpu"] == 3
    assert config["storage"] == round_up(-4.25877 +
                                         0.98271 * math.log(2000), 3)


def test_processor_replicas_3_memory():
    processor = Processor()
    processor.update_config(
        agents=2000,
        storage=500,
        traffic=50,
        mail_traffic=300,
        distributed=True,
        nodes=5)
    config = processor.get_config()
    assert config["replicas"] == 3
    assert config["memory"] == 50 * 0.5
    assert config["cpu"] == 3
    assert config["storage"] == round_up(-4.25877 +
                                         0.98271 * math.log(2000), 3)


def test_processor_storage():
    processor = Processor()
    processor.update_config(
        agents=2000,
        storage=500,
        traffic=530,
        mail_traffic=300,
        distributed=True,
        nodes=0)
    config = processor.get_config()
    assert config["replicas"] == 3
    assert config["memory"] == 530 * 0.5
    assert config["cpu"] == 3
    assert config["storage"] == 0


def test_processor_mixed():
    processor = Processor()
    processor.update_config(
        agents=1,
        storage=500,
        traffic=530,
        mail_traffic=300,
        distributed=False,
        nodes=3)
    config = processor.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 100
    assert config["cpu"] == 3
    assert config["storage"] == round_up(-4.25877 + 0.98271 * math.log(1), 3)
