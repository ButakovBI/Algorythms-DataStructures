from services.base import ServiceBase


class ElasticSearch(ServiceBase):
    def update_config(self, agents: int,
                      distributed: bool,
                      storage: float = None,
                      traffic: float = None,
                      mail_traffic: float = None,
                      nodes: int = None) -> None:

        self._replicas = 3 if distributed else 1
        self._memory = 0
        self._cpu = 3
        if agents < 5000:
            self._storage = 0.256
        elif agents < 10000:
            self._storage = 0.512
        else:
            self._storage = 1