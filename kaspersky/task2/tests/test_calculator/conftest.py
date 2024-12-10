import pytest

from services.base import ServiceBase
from services.clickhouse import Clickhouse
from services.kafka import Kafka
from services.scanner import Scanner


class MockService(ServiceBase):
    def update_config(self, **kwargs):
        pass


class NewYearService(ServiceBase):
    def update_config(self, agents: int,
                      distributed: bool,
                      storage: float = None,
                      traffic: float = None,
                      mail_traffic: float = None,
                      nodes: int = None) -> None:
        self._replicas = 1 if agents > 12345 else 0
        self._memory = 10000
        self._cpu = 1
        self._storage = 2025 if storage > 2024 else 2024
    

@pytest.fixture
def sample_registered_services():
    return {
        "newyearservice": NewYearService,
        "kafka": Kafka,
        "mockservice": MockService,
        "clickhouse": Clickhouse,
        "scanner": Scanner
    }


@pytest.fixture
def sample_params():
    return {
        "agents": 5,
        "storage": 10,
        "traffic": 20,
        "mail_traffic": 15,
        "distributed": True,
        "nodes": 3,
    }


@pytest.fixture
def sample_config():
    return {
        "scanner": {
            "replicas": 1,
            "memory": 256.4,
            "cpu": 2,
            "storage": 7823.12
        },
        "database_server": {
            "replicas": 3,
            "memory": 512.9,
            "cpu": 4,
            "storage": 10234.78
        },
        "newyearservice": {
            "replicas":12,
            "memory": 3,
            "cpu": 2,
            "storage":10000
        },
        "whoknows": {
            "replicas": 0,
            "memory": 0,
            "cpu": 2,
            "storage": 0
        }, 
        "kafka": {
            "replicas": 2,
            "memory": 128.5,
            "cpu": 3,
            "storage": 6345.22
        },

    }


@pytest.fixture
def empty_config():
    return {}


@pytest.fixture
def not_full_config():
    return {
        "clickhouse": {
            "replicas":12,
            "storage":10000
        },
        "scanner": {
            "replicas": 0,
            "memory": 0,
            "storage": 0,
            "cpu": 1234.543
        }, 
        "kafka": {

        },
    }