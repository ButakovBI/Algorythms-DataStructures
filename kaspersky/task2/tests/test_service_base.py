from services.base import ServiceBase


class MockService(ServiceBase):
    def update_config(self, **kwargs):
        pass


def test_service_base_initialization():
    service = MockService()
    config = service.get_config()
    assert config["replicas"] == 0
    assert config["memory"] == 0
    assert config["cpu"] == 0
    assert config["storage"] == 0
